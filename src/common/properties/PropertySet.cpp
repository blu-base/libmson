#include "PropertySet.h"
#include <QDebug>

#include "PropertyType_ArrayNumber.h"
#include "PropertyType_ArrayOfPropertyValues.h"
#include "PropertyType_EightBytesOfData.h"
#include "PropertyType_FourBytesOfData.h"
#include "PropertyType_FourBytesOfLengthFollowedByData.h"
#include "PropertyType_NoData.h"
#include "PropertyType_OneByteOfData.h"
#include "PropertyType_PropertySet.h"
#include "PropertyType_TwoBytesOfData.h"

#include "../helper/Helper.h"

#include "../simpleTypes/LayoutAlignment.h"

quint16 PropertySet::cProperties() const { return m_cProperties; }

void PropertySet::setCProperties(const quint16 &cProperties) {
  m_cProperties = cProperties;
}

std::vector<PropertyID> PropertySet::rgPrids() const { return m_rgPrids; }

void PropertySet::setRgPrids(const std::vector<PropertyID> &rgPrids) {
  m_rgPrids = rgPrids;
}

std::vector<IPropertyType *> PropertySet::rgData() const { return m_rgData; }

void PropertySet::setRgData(const std::vector<IPropertyType *> &rgData) {
  m_rgData = rgData;
}

/// \todo implement propertyset
void PropertySet::deserialize(QDataStream &ds) {

  quint64 curLocation = ds.device()->pos();
  ds >> m_cProperties;

  for (quint32 i = 0; i < m_cProperties; i++) {
    PropertyID prid;
    ds >> prid;
    m_rgPrids.push_back(prid);
  }

  for (const auto &propID : m_rgPrids) {
    quint64 curLocation = ds.device()->pos();
    IPropertyType *prop = nullptr;

    switch (propID.type()) {
    case PropertyIDType::NoData:
    case PropertyIDType::Bool:
    case PropertyIDType::ObjectID:
    case PropertyIDType::ContextID:
    case PropertyIDType::ObjectSpaceID:
      prop = new PropertyType_NoData();
      break;

    case PropertyIDType::ArrayOfObjectIDs:
    case PropertyIDType::ArrayOfObjectSpaceIDs:
    case PropertyIDType::ArrayOfContextIDs:
      prop = new PropertyType_ArrayNumber();
      break;

    case PropertyIDType::OneByteOfData:
      prop = new PropertyType_OneByteOfData();
      break;

    case PropertyIDType::TwoBytesOfData:
      prop = new PropertyType_TwoBytesOfData();
      break;

    case PropertyIDType::FourBytesOfData:
      prop = new PropertyType_FourBytesOfData();
      break;

    case PropertyIDType::EightBytesOfData:
      prop = new PropertyType_EightBytesOfData();
      break;

    case PropertyIDType::FourBytesOfLengthFollowedByData:
      prop = new PropertyType_FourBytesOfLengthFollowedByData();
      break;

    case PropertyIDType::ArrayOfPropertyValues:
      prop = new PropertyType_ArrayOfPropertyValues();
      break;

    case PropertyIDType::PropertySet:
      prop = new PropertyType_PropertySet();
      break;

    default:
      break;
    }

    //        if (propID.type() == PropertyIDType::PropertySet) {
    //            qWarning() << "Encountered PropertySetElement of type
    //            PropertySet"; break;
    //        }

    //    if (propID.type() == PropertyIDType::InvalidType) {
    //      qWarning() << "Encountered invalid PropertyType";
    //      break;
    //    }

    if (prop != nullptr) {
      ds >> *prop;
    }
    m_rgData.push_back(prop);
  }
}

void PropertySet::serialize(QDataStream &ds) const {

  ds << m_cProperties;

  for (auto propid : m_rgPrids) {
    ds << propid;
  }

  for (IPropertyType *prop : m_rgData) {
    ds << *prop;
  }
}

void PropertySet::toDebugString(QDebug dbg) const {}

PropertySet::PropertySet() : m_cProperties{} {}

void PropertySet::generateXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("PropertySet");
  xmlWriter.writeAttribute("cProperties", QString::number(m_cProperties));

  xmlWriter.writeStartElement("rgPrids");
  for (size_t i{0}; i < m_rgPrids.size(); i++) {
    xmlWriter.writeStartElement("PropertyID");

    xmlWriter.writeAttribute("ID", PropertyID::idToString(m_rgPrids[i].id()));

    xmlWriter.writeAttribute("Type",
                             PropertyID::typeToString(m_rgPrids[i].type()));
    xmlWriter.writeAttribute("boolValue",
                             m_rgPrids[i].boolValue() ? "True" : "False");
    xmlWriter.writeAttribute("Value", qStringHex(m_rgPrids[i].value(), 8));

    switch (m_rgPrids[i].id()) {
    case PropertyIDs::LayoutTightLayout:
      break;
    case PropertyIDs::PageWidth: {
      xmlWriter.writeStartElement("PageWidth");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float pagewidth;
      bytes >> pagewidth;
      // Validity specified by MS-ONE, sec 2.3.6
      if (pagewidth < 2.0 || pagewidth > 44.0) {
        xmlWriter.writeAttribute("valid", "False");
      }
      xmlWriter.writeCharacters(QString::number(pagewidth, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageHeight: {
      xmlWriter.writeStartElement("PageHeight");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float pageheight;
      bytes >> pageheight;
      // Validity specified by MS-ONE, sec 2.3.7,
      // though does not check: (PageMarginTop + PageMarginBottom + 0.5 <
      // pageheight)
      if (pageheight < 0.5 || pageheight > 44.0) {
        xmlWriter.writeAttribute("valid", "False");
      }
      xmlWriter.writeCharacters(QString::number(pageheight, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::OutlineElementChildLevel: {
      xmlWriter.writeStartElement("IndentationLevel");
      auto *body = static_cast<PropertyType_OneByteOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());

      uint8_t val;
      bytes >> val;

      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Bold:
    case PropertyIDs::Italic:
    case PropertyIDs::Underline:
    case PropertyIDs::Strikethrough:
    case PropertyIDs::Superscript:
    case PropertyIDs::Subscript:
      break;

    case PropertyIDs::Font: {
      xmlWriter.writeStartElement("Font");
      if (m_rgPrids[i].type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
            m_rgData[i]);
        QString string =
            QString::fromUtf8(body->data().constData(), body->cb());
        xmlWriter.writeCharacters(string);
      }
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::FontSize: {
      xmlWriter.writeStartElement("FontSize");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      uint16_t val;
      bytes >> val;
      // validity given by MS-ONE sec 2.3.16
      if (val < 12 || val > 288) {
        xmlWriter.writeAttribute("valid", "false");
      }
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::FontColor: {
      xmlWriter.writeStartElement("COLORREF");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QString string = body->data().toHex();
      xmlWriter.writeCharacters("0x" + string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Highlight: {
      xmlWriter.writeStartElement("COLORREF");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QString string = body->data().toHex();
      xmlWriter.writeCharacters("0x" + string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::RgOutlineIndentDistance: {
      xmlWriter.writeStartElement("RgOutlineIndentDistance");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      uint8_t count;
      bytes >> count;
      xmlWriter.writeAttribute("count", QString::number(count));
      char *rawBody = new char[3];
      bytes.readRawData(rawBody, 3);
      QByteArray unused = QByteArray(QByteArray::fromRawData(rawBody, 3));
      xmlWriter.writeAttribute("unused-bytes", unused.toHex());

      for (size_t j = 0; j < count; j++) {
        float indentation;
        bytes >> indentation;
        xmlWriter.writeStartElement("IndentDistance");
        xmlWriter.writeCharacters(QString::number(indentation, 'f', 5));
        xmlWriter.writeEndElement();
      }
      xmlWriter.writeEndElement();
      break;
    }
      //          case PropertyIDs::BodyTextAlignment:
      //            break;
    case PropertyIDs::OffsetFromParentHoriz: {
      xmlWriter.writeStartElement("OffsetFromParentHoriz");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::OffsetFromParentVert: {
      xmlWriter.writeStartElement("OffsetFromParentVert");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs:::
      //      m_id_string = "NumberListFormat";
      //      break;
    case PropertyIDs::LayoutMaxWidth: {
      xmlWriter.writeStartElement("LayoutMaxWidth");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutMaxHeight: {
      xmlWriter.writeStartElement("LayoutMaxHeight");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::ContentChildNodes:
      //      m_id_string = "ContentChildNodes";
      //      break;
      //    case PropertyIDs::ElementChildNodes:
      //      m_id_string = "ElementChildNodes";
      //      break;
      //    case PropertyIDs::EnableHistory:
      //      m_id_string = "EnableHistory";
      //      break;
    case PropertyIDs::RichEditTextUnicode: {
      xmlWriter.writeStartElement("RichEditTextUnicode");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort *>(body->data().constData()));

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::ListNodes:
      //      m_id_string = "ListNodes";
      //      break;
    case PropertyIDs::NotebookManagementEntityGuid: {
      xmlWriter.writeStartElement("NotebookManagementEntityGuid");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      QUuid val;
      bytes >> val;
      xmlWriter.writeCharacters(val.toString());
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::OutlineElementRTL:
      break;
      //    case PropertyIDs::LanguageID:
      //      m_id_string = "LanguageID";
      //      break;
    case PropertyIDs::LayoutAlignmentInParent: {
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      LayoutAlignment val;
      bytes >> val;
      val.generateXml(xmlWriter);
      break;
    }
      //    case PropertyIDs::PictureContainer:
      //      m_id_string = "PictureContainer";
      //      break;
    case PropertyIDs::PageMarginTop: {
      xmlWriter.writeStartElement("PageMarginTop");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageMarginBottom: {
      xmlWriter.writeStartElement("PageMarginBottom");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageMarginLeft: {
      xmlWriter.writeStartElement("PageMarginLeft");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageMarginRight: {
      xmlWriter.writeStartElement("PageMarginRight");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ListFont: {
      xmlWriter.writeStartElement("ListFont");
      if (m_rgPrids[i].type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
            m_rgData[i]);
        QString string =
            QString::fromUtf8(body->data().constData(), body->cb());
        xmlWriter.writeCharacters(string);
      }
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::TopologyCreationTimeStamp:
      //      m_id_string = "TopologyCreationTimeStamp";
      //      break;
      //    case PropertyIDs::LayoutAlignmentSelf:
      //      m_id_string = "LayoutAlignmentSelf";
      //      break;
    case PropertyIDs::IsTitleTime:
    case PropertyIDs::IsBoilerText:
      break;
      //    case PropertyIDs::PageSize:
      //      m_id_string = "PageSize";
      //      break;
    case PropertyIDs::LayoutResolveChildCollisions:
    case PropertyIDs::PortraitPage:
    case PropertyIDs::EnforceOutlineStructure:
    case PropertyIDs::EditRootRTL:
    case PropertyIDs::CannotBeSelected:
    case PropertyIDs::IsTitleText:
    case PropertyIDs::IsTitleDate:
      break;
      //    case PropertyIDs::ListRestart:
      //      m_id_string = "ListRestart";
      //      break;
      //    case PropertyIDs::IsLayoutSizeSetByUser:
      //      m_id_string = "IsLayoutSizeSetByUser";
      //      break;
      //    case PropertyIDs::ListSpacingMu:
      //      m_id_string = "ListSpacingMu";
      //      break;
      //    case PropertyIDs::LayoutOutlineReservedWidth:
      //      m_id_string = "LayoutOutlineReservedWidth";
      //      break;
      //    case PropertyIDs::LayoutResolveChildCollisions:
      //      m_id_string = "LayoutResolveChildCollisions";
      //      break;
    case PropertyIDs::IsReadOnly:
      break;
      //    case PropertyIDs::LayoutMinimumOutlineWidth:
      //      m_id_string = "LayoutMinimumOutlineWidth";
      //      break;
      //    case PropertyIDs::LayoutCollisionPriority:
      //      m_id_string = "LayoutCollisionPriority";
      //      break;
    case PropertyIDs::CachedTitleString: {
      xmlWriter.writeStartElement("wz");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QString string = QString::fromUtf8(body->data().constData(), body->cb());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::DescendantsCannotBeMoved:
      //      m_id_string = "DescendantsCannotBeMoved";
      //      break;
      //    case PropertyIDs::RichEditTextLangID:
      //      m_id_string = "RichEditTextLangID";
      //      break;
      //    case PropertyIDs::LayoutTightAlignment:
      //      m_id_string = "LayoutTightAlignment";
      //      break;
      //    case PropertyIDs::Charset:
      //      m_id_string = "Charset";
      //      break;
      //    case PropertyIDs::CreationTimeStamp:
      //      m_id_string = "CreationTimeStamp";
      //      break;
    case PropertyIDs::Deletable:
      break;
      //    case PropertyIDs::ListMSAAIndex:
      //      m_id_string = "ListMSAAIndex";
      //      break;
      //    case PropertyIDs::IsBackground:
      //      m_id_string = "IsBackground";
      //      break;
      //    case PropertyIDs::IRecordMedia:
      //      m_id_string = "IRecordMedia";
      //      break;
    case PropertyIDs::CachedTitleStringFromPage: {
      xmlWriter.writeStartElement("wz");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QString string = QString::fromUtf8(body->data().constData(), body->cb());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::RowCount:
      //      m_id_string = "RowCount";
      //      break;
      //    case PropertyIDs::ColumnCount:
      //      m_id_string = "ColumnCount";
      //      break;
      //    case PropertyIDs::TableBordersVisible:
      //      m_id_string = "TableBordersVisible";
      //      break;
      //    case PropertyIDs::StructureElementChildNodes:
      //      m_id_string = "StructureElementChildNodes";
      //      break;
      //    case PropertyIDs::ChildGraphSpaceElementNodes:
      //      m_id_string = "ChildGraphSpaceElementNodes";
      //      break;
      //    case PropertyIDs::TableColumnWidths:
      //      m_id_string = "TableColumnWidths";
      //      break;
    case PropertyIDs::Author: {
      xmlWriter.writeStartElement("Author");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort *>(body->data().constData()));

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }

      //    case PropertyIDs::LastModifiedTimeStamp:
      //      m_id_string = "LastModifiedTimeStamp";
      //      break;
      //    case PropertyIDs::AuthorOriginal:
      //      m_id_string = "AuthorOriginal";
      //      break;
      //    case PropertyIDs::AuthorMostRecent:
      //      m_id_string = "AuthorMostRecent";
      //      break;
      //    case PropertyIDs::LastModifiedTime:
      //      m_id_string = "LastModifiedTime";
      //      break;
      //    case PropertyIDs::IsConflictPage:
      //      m_id_string = "IsConflictPage";
      //      break;
      //    case PropertyIDs::TableColumnsLocked:
      //      m_id_string = "TableColumnsLocked";
      //      break;
      //    case PropertyIDs::SchemaRevisionInOrderToRead:
      //      m_id_string = "SchemaRevisionInOrderToRead";
      //      break;
      //    case PropertyIDs::IsConflictObjectForRender:
      //      m_id_string = "IsConflictObjectForRender";
      //      break;
      //    case PropertyIDs::EmbeddedFileContainer:
      //      m_id_string = "EmbeddedFileContainer";
      //      break;
    case PropertyIDs::EmbeddedFileName: {
      xmlWriter.writeStartElement("EmbeddedFileName");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort *>(body->data().constData()));

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::SourceFilepath: {
      xmlWriter.writeStartElement("SourceFilepath");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort *>(body->data().constData()));

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::ConflictingUserName:
      //      m_id_string = "ConflictingUserName";
      //      break;
    case PropertyIDs::ImageFilename: {
      xmlWriter.writeStartElement("ImageFilename");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort *>(body->data().constData()));

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::IsConflictObjectForSelection:
      //      m_id_string = "IsConflictObjectForSelection";
      //      break;
      //    case PropertyIDs::PageLevel:
      //      m_id_string = "PageLevel";
      //      break;
      //    case PropertyIDs::TextRunIndex:
      //      m_id_string = "TextRunIndex";
      //      break;
      //    case PropertyIDs::TextRunFormatting:
      //      m_id_string = "TextRunFormatting";
      //      break;
    case PropertyIDs::Hyperlink:
      break;
      //    case PropertyIDs::UnderlineType:
      //      m_id_string = "UnderlineType";
      //      break;
    case PropertyIDs::Hidden:
    case PropertyIDs::HyperlinkProtected:
      break;
      //    case PropertyIDs::TextRunIsEmbeddedObject:
      //      m_id_string = "TextRunIsEmbeddedObject";
      //      break;
      //    case PropertyIDs::ImageAltText:
      //      m_id_string = "ImageAltText";
      //      break;
    case PropertyIDs::MathFormatting:
      break;
      //    case PropertyIDs::ParagraphStyle: {
      //      break;
      //    }
      //    case PropertyIDs::ParagraphSpaceBefore:
      //      m_id_string = "ParagraphSpaceBefore";
      //      break;
      //    case PropertyIDs::ParagraphSpaceAfter:
      //      m_id_string = "ParagraphSpaceAfter";
      //      break;
      //    case PropertyIDs::ParagraphLineSpacingExact:
      //      m_id_string = "ParagraphLineSpacingExact";
      //      break;
      //    case PropertyIDs::MetaDataObjectsAboveGraphSpace:
      //      m_id_string = "MetaDataObjectsAboveGraphSpace";
      //      break;
      //    case PropertyIDs::TextRunDataObject:
      //      m_id_string = "TextRunDataObject";
      //      break;
      //    case PropertyIDs::TextRunData:
      //      m_id_string = "TextRunData";
      //      break;
    case PropertyIDs::ParagraphStyleId: {
      xmlWriter.writeStartElement("ParagraphStyleId");
      if (m_rgPrids[i].type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
            m_rgData[i]);
        QString string =
            QString::fromUtf8(body->data().constData(), body->cb());
        xmlWriter.writeCharacters(string);
      }
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::HasVersionPages:
      //      m_id_string = "HasVersionPages";
      //      break;
      //    case PropertyIDs::ActionItemType:
      //      m_id_string = "ActionItemType";
      //      break;
      //    case PropertyIDs::NoteTagShape:
      //      m_id_string = "NoteTagShape";
      //      break;
      //    case PropertyIDs::NoteTagHighlightColor:
      //      m_id_string = "NoteTagHighlightColor";
      //      break;
      //    case PropertyIDs::NoteTagTextColor:
      //      m_id_string = "NoteTagTextColor";
      //      break;
      //    case PropertyIDs::NoteTagPropertyStatus:
      //      m_id_string = "NoteTagPropertyStatus";
      //      break;
      //    case PropertyIDs::NoteTagLabel:
      //      m_id_string = "NoteTagLabel";
      //      break;
      //    case PropertyIDs::NoteTagCreated:
      //      m_id_string = "NoteTagCreated";
      //      break;
      //    case PropertyIDs::NoteTagCompleted:
      //      m_id_string = "NoteTagCompleted";
      //      break;
      //    case PropertyIDs::NoteTagDefinitionOid:
      //      m_id_string = "NoteTagDefinitionOid";
      //      break;
      //    case PropertyIDs::NoteTagStates:
      //      m_id_string = "NoteTagStates";
      //      break;
      //    case PropertyIDs::ActionItemStatus:
      //      m_id_string = "ActionItemStatus";
      //      break;
      //    case PropertyIDs::ActionItemSchemaVersion:
      //      m_id_string = "ActionItemSchemaVersion";
      //      break;
      //    case PropertyIDs::ReadingOrderRTL:
      //      m_id_string = "ReadingOrderRTL";
      //      break;
      //    case PropertyIDs::ParagraphAlignment:
      //      m_id_string = "ParagraphAlignment";
      //      break;
      //    case PropertyIDs::VersionHistoryGraphSpaceContextNodes:
      //      m_id_string = "VersionHistoryGraphSpaceContextNodes";
      //      break;
      //    case PropertyIDs::DisplayedPageNumber:
      //      m_id_string = "DisplayedPageNumber";
      //      break;
      //    case PropertyIDs::SectionDisplayName:
      //      m_id_string = "SectionDisplayName";
      //      break;
      //    case PropertyIDs::NextStyle:
      //      m_id_string = "NextStyle";
      //      break;
      //    case PropertyIDs::WebPictureContainer14:
      //      m_id_string = "WebPictureContainer14";
      //      break;
      //    case PropertyIDs::ImageUploadState:
      //      m_id_string = "ImageUploadState";
      //      break;
    case PropertyIDs::TextExtendedAscii: {
      xmlWriter.writeStartElement("String");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QString string = QString::fromUtf8(body->data().constData(), body->cb());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::PictureWidth:
      //      m_id_string = "PictureWidth";
      //      break;
      //    case PropertyIDs::PictureHeight:
      //      m_id_string = "PictureHeight";
      //      break;
    case PropertyIDs::PageMarginOriginX: {
      xmlWriter.writeStartElement("PageMarginOriginX");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageMarginOriginY: {
      xmlWriter.writeStartElement("PageMarginOriginY");
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::WzHyperlinkUrl:
      //      m_id_string = "WzHyperlinkUrl";
      //      break;
      //    case PropertyIDs::TaskTagDueDate:
      //      m_id_string = "TaskTagDueDate";
      //      break;
    case PropertyIDs::AuthorInitials: {
      xmlWriter.writeStartElement("AuthorInitials");
      if (m_rgPrids[i].type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
            m_rgData[i]);
        QString string =
            QString::fromUtf8(body->data().constData(), body->cb());
        xmlWriter.writeCharacters(string);
      }
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ResolutionID: {
      xmlWriter.writeStartElement("ResolutionID");
      if (m_rgPrids[i].type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
            m_rgData[i]);
        QString string =
            QString::fromUtf8(body->data().constData(), body->cb());
        xmlWriter.writeCharacters(string);
      }
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::None:
    default:
      m_rgData[i]->generateXml(xmlWriter);
      break;
    }
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();

  xmlWriter.writeEndElement();
}

QDataStream &operator<<(QDataStream &ds, const PropertySet &obj) {
  obj.serialize(ds);
  return ds;
}

QDataStream &operator>>(QDataStream &ds, PropertySet &obj) {
  obj.deserialize(ds);
  return ds;
}

QDebug operator<<(QDebug dbg, const PropertySet &obj) {
  obj.toDebugString(dbg);
  return dbg;
}
