#include "PropertySet.h"
#include <QDebug>
#include <algorithm>

#include "PropertyType_ArrayNumber.h"
#include "PropertyType_ArrayOfPropertyValues.h"
#include "PropertyType_EightBytesOfData.h"
#include "PropertyType_FourBytesOfData.h"
#include "PropertyType_FourBytesOfLengthFollowedByData.h"
#include "PropertyType_NoData.h"
#include "PropertyType_ObjectID.h"
#include "PropertyType_OneByteOfData.h"
#include "PropertyType_PropertySet.h"
#include "PropertyType_TwoBytesOfData.h"

#include "../helper/Helper.h"

#include "../simpleTypes/BodyTextAlignment.h"
#include "../simpleTypes/ColorRef.h"
#include "../simpleTypes/FileTime.h"
#include "../simpleTypes/LCID.h"
#include "../simpleTypes/LayoutAlignment.h"
#include "../simpleTypes/ListMSAAIndex.h"
#include "../simpleTypes/NoteTagShape.h"
#include "../simpleTypes/PageSize.h"
#include "../simpleTypes/Time32.h"

namespace MSONcommon {

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
    /// \todo fix memory leak here
    IPropertyType *prop = nullptr;

    switch (propID.type()) {
    case PropertyIDType::NoData:
    case PropertyIDType::Bool:
    case PropertyIDType::ContextID:
    case PropertyIDType::ObjectSpaceID:
    case PropertyIDType::ObjectID:
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

void PropertySet::toDebugString(QDebug &dbg) const {}

PropertySet::PropertySet() : m_cProperties{} {}

/// \todo utf16 and utf8 might end prematurely because \0 terminator found
void PropertySet::writeLowLevelXml(QXmlStreamWriter &xmlWriter) const {
  xmlWriter.writeStartElement("PropertySet");
  xmlWriter.writeAttribute("cProperties", QString::number(m_cProperties));

  for (size_t i{0}; i < m_rgPrids.size(); i++) {
    xmlWriter.writeStartElement("PropertyID");

    xmlWriter.writeAttribute("ID", PropertyID::idToString(m_rgPrids[i].id()));

    xmlWriter.writeAttribute("Type",
                             PropertyID::typeToString(m_rgPrids[i].type()));
    xmlWriter.writeAttribute("boolValue",
                             m_rgPrids[i].boolValue() ? "True" : "False");
    xmlWriter.writeAttribute("Value", qStringHex(m_rgPrids[i].value(), 8));

    switch (m_rgPrids[i].id()) {
    case PropertyIDs::LayoutTightLayout: {
      xmlWriter.writeStartElement("LayoutTightLayout");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageWidth: {
      xmlWriter.writeStartElement("PageWidth");
      const auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
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
      const auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
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
      const auto body =
          static_cast<PropertyType_OneByteOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);

      uint8_t val;
      bytes >> val;

      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Bold: {
      xmlWriter.writeStartElement("Bold");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Italic: {
      xmlWriter.writeStartElement("Italic");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Underline: {
      xmlWriter.writeStartElement("Underline");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Strikethrough: {
      xmlWriter.writeStartElement("Strikethrough");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Superscript: {
      xmlWriter.writeStartElement("Superscript");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Subscript: {
      xmlWriter.writeStartElement("Subscript");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::Font: {
      xmlWriter.writeStartElement("Font");
      if (m_rgPrids[i].type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        const auto body =
            static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
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
      const auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      uint16_t val;
      bytes >> val;
      // validity given by MS-ONE sec 2.3.16
      if (val < 12 || val > 288) {
        xmlWriter.writeAttribute("valid", "false");
      }
      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::FontColor: {
      xmlWriter.writeStartElement("FontColor");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      ColorRef val;
      bytes >> val;

      xmlWriter << val;

      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Highlight: {
      xmlWriter.writeStartElement("Highlight");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      ColorRef val;
      bytes >> val;

      xmlWriter << val;
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::RgOutlineIndentDistance: {
      xmlWriter.writeStartElement("RgOutlineIndentDistance");
      const auto body =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i])
              ->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint8 count;
      bytes >> count;
      xmlWriter.writeAttribute("count", QString::number(count));
      const QByteArray unused = bytes.device()->read(3);
      xmlWriter.writeAttribute("unused-bytes", unused.toHex());

      xmlWriter.writeStartElement("rgIndents");
      xmlWriter.writeCharacters("{");
      for (quint8 j = 0; j < count; j++) {
        float distance;
        bytes >> distance;
        xmlWriter.writeCharacters(QString::number(distance, 'f', 5));

        if (j + 1 != count) {
          xmlWriter.writeCharacters(", ");
        }
      }
      xmlWriter.writeCharacters("}");
      xmlWriter.writeEndElement();

      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::BodyTextAlignment: {
      const auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      BodyTextAlignment bta;
      QDataStream bytes(body);
      bytes >> bta;
      xmlWriter << bta;
      break;
    }
    case PropertyIDs::OffsetFromParentHoriz: {
      xmlWriter.writeStartElement("OffsetFromParentHoriz");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
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
      const auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::NumberListFormat:
      //      m_id_string = "NumberListFormat";
      //      break;
    case PropertyIDs::LayoutMaxWidth: {
      xmlWriter.writeStartElement("LayoutMaxWidth");
      const auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
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
      const auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
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
    case PropertyIDs::EnableHistory: {
      xmlWriter.writeStartElement("EnableHistory");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::RichEditTextUnicode: {
      xmlWriter.writeStartElement("RichEditTextUnicode");
      const auto data =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i])
              ->data();
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort *>(data.constData()), data.size() / 2);

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::ListNodes:
      //      m_id_string = "ListNodes";
      //      break;
    case PropertyIDs::NotebookManagementEntityGuid: {
      xmlWriter.writeStartElement("NotebookManagementEntityGuid");
      const auto body =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i])
              ->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      QUuid val;
      bytes >> val;
      xmlWriter.writeCharacters(val.toString());
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::OutlineElementRTL: {
      xmlWriter.writeStartElement("OutlineElementRTL");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::LanguageID: {
      xmlWriter.writeStartElement("LanguageID");
      const auto body =
          static_cast<PropertyType_TwoBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      LCID val;
      bytes >> val;
      xmlWriter.writeCharacters(val.toString());
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutAlignmentInParent: {
      const auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
      LayoutAlignment val;
      bytes >> val;
      xmlWriter << val;
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
    case PropertyIDs::TopologyCreationTimeStamp: {
      xmlWriter.writeStartElement("TopologyCreationTimeStamp");
      auto body =
          static_cast<PropertyType_EightBytesOfData *>(m_rgData[i])->data();

      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      FileTime time;
      bytes >> time;
      xmlWriter.writeCharacters(
          time.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutAlignmentSelf: {
      auto body = static_cast<PropertyType_FourBytesOfData *>(m_rgData[i]);
      QDataStream bytes(body->data());
      LayoutAlignment val;
      bytes >> val;
      xmlWriter << val;
      break;
    }
    case PropertyIDs::IsTitleTime: {
      xmlWriter.writeStartElement("IsTitleTime");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsBoilerText: {
      xmlWriter.writeStartElement("IsBoilerText");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageSize: {
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      PageSize ps;
      bytes >> ps;
      xmlWriter << ps;
      break;
    }

    case PropertyIDs::PortraitPage: {
      xmlWriter.writeStartElement("PortraitPage");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::EnforceOutlineStructure: {
      xmlWriter.writeStartElement("EnforceOutlineStructure");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::EditRootRTL: {
      xmlWriter.writeStartElement("EditRootRTL");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::CannotBeSelected: {
      xmlWriter.writeStartElement("CannotBeSelected");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsTitleText: {
      xmlWriter.writeStartElement("IsTitleText");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsTitleDate: {
      xmlWriter.writeStartElement("IsTitleDate");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ListRestart: {
      auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);

      quint32 val;
      bytes >> val;

      xmlWriter.writeStartElement("ListRestart");
      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsLayoutSizeSetByUser: {
      xmlWriter.writeStartElement("IsLayoutSizeSetByUser");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ListSpacingMu: {
      auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;

      xmlWriter.writeStartElement("ListSpacingMu");
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutOutlineReservedWidth: {
      auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;

      xmlWriter.writeStartElement("LayoutOutlineReservedWidth");
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::LayoutResolveChildCollisions: {
      xmlWriter.writeStartElement("LayoutResolveChildCollisions");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::IsReadOnly: {
      xmlWriter.writeStartElement("IsReadOnly");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutMinimumOutlineWidth: {
      xmlWriter.writeStartElement("LayoutMinimumOutlineWidth");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutCollisionPriority: {
      auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      quint32 val;
      bytes >> val;

      xmlWriter.writeStartElement("LayoutCollisionPriority");
      xmlWriter.writeCharacters(qStringHex(val, 8));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::CachedTitleString: {
      xmlWriter.writeStartElement("wz");
      const auto body =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i]);
      QString string = QString::fromUtf8(body->data().constData(), body->cb());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::DescendantsCannotBeMoved: {
      xmlWriter.writeStartElement("DescendantsCannotBeMoved");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::RichEditTextLangID: {
      xmlWriter.writeStartElement("RichEditTextLangID");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      LCID val;
      bytes >> val;
      xmlWriter.writeCharacters(val.toString());
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LayoutTightAlignment: {
      xmlWriter.writeStartElement("LayoutTightAlignment");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Charset: {
      xmlWriter.writeStartElement("Charset");
      auto data =
          static_cast<PropertyType_OneByteOfData *>(m_rgData[i])->data();
      QString string;
      switch (static_cast<Charset>(data.toUInt())) {
      case Charset::ANSI_CHARSET:
        string = "ANSI_CHARSET";
        break;
      case Charset::DEFAULT_CHARSET:
        string = "DEFAULT_CHARSET";
        break;
      case Charset::SYMBOL_CHARSET:
        string = "SYMBOL_CHARSET";
        break;
      case Charset::MAC_CHARSET:
        string = "MAC_CHARSET";
        break;
      case Charset::SHIFTJIS_CHARSET:
        string = "SHIFTJIS_CHARSET";
        break;
      case Charset::HANGUL_CHARSET:
        string = "HANGUL_CHARSET";
        break;
      case Charset::JOHAB_CHARSET:
        string = "JOHAB_CHARSET";
        break;
      case Charset::GB2312_CHARSET:
        string = "GB2312_CHARSET";
        break;
      case Charset::CHINESEBIG5_CHARSET:
        string = "CHINESEBIG5_CHARSET";
        break;
      case Charset::GREEK_CHARSET:
        string = "GREEK_CHARSET";
        break;
      case Charset::TURKISH_CHARSET:
        string = "TURKISH_CHARSET";
        break;
      case Charset::VIETNAMESE_CHARSET:
        string = "VIETNAMESE_CHARSET";
        break;
      case Charset::HEBREW_CHARSET:
        string = "HEBREW_CHARSET";
        break;
      case Charset::ARABIC_CHARSET:
        string = "ARABIC_CHARSET";
        break;
      case Charset::BALTIC_CHARSET:
        string = "BALTIC_CHARSET";
        break;
      case Charset::RUSSIAN_CHARSET:
        string = "RUSSIAN_CHARSET";
        break;
      case Charset::THAI_CHARSET:
        string = "THAI_CHARSET";
        break;
      case Charset::EASTEUROPE_CHARSET:
        string = "EASTEUROPE_CHARSET";
        break;
      case Charset::OEM_CHARSET:
        string = "OEM_CHARSET";
        break;
      }
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::CreationTimeStamp: {
      xmlWriter.writeStartElement("CreationTimeStamp");
      auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      Time32 time;
      bytes >> time;
      xmlWriter.writeCharacters(
          time.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Deletable: {
      xmlWriter.writeStartElement("Deletable");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ListMSAAIndex: {
      auto data =
          static_cast<PropertyType_TwoBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);

      ListMSAAIndex index;
      bytes >> index;

      xmlWriter << index;

      break;
    }
    case PropertyIDs::IsBackground: {
      xmlWriter.writeStartElement("IsBackground");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::IRecordMedia: {
      xmlWriter.writeStartElement("IRecordMedia");
      auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(val == 1 ? "Audio"
                                         : (val == 2 ? "Video" : "invalid"));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::CachedTitleStringFromPage: {
      xmlWriter.writeStartElement("wz");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QString string = QString::fromUtf8(body->data().constData(), body->cb());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::RowCount: {
      xmlWriter.writeStartElement("RowCount");
      auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ColumnCount: {
      xmlWriter.writeStartElement("ColumnCount");
      auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::TableBordersVisible: {
      xmlWriter.writeStartElement("TableBordersVisible");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }

      //    case PropertyIDs::StructureElementChildNodes:
      //      m_id_string = "StructureElementChildNodes";
      //      break;
      //    case PropertyIDs::ChildGraphSpaceElementNodes:
      //      m_id_string = "ChildGraphSpaceElementNodes";
      //      break;
    case PropertyIDs::TableColumnWidths: {
      xmlWriter.writeStartElement("TableColumnWidths");
      const auto data =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i])
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      quint8 cColumns;
      bytes >> cColumns;

      xmlWriter.writeAttribute("cColumns", QString::number(cColumns));

      xmlWriter.writeCharacters("{");
      for (quint8 j = 0; j < cColumns; j++) {
        float width;
        bytes >> width;
        xmlWriter.writeCharacters(QString::number(width, 'f', 5));

        if (j + 1 != cColumns) {
          xmlWriter.writeCharacters(", ");
        }
      }
      xmlWriter.writeCharacters("}");
      xmlWriter.writeEndElement();
      break;
    }

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

    case PropertyIDs::LastModifiedTimeStamp: {
      xmlWriter.writeStartElement("LastModifiedTimeStamp");
      auto body =
          static_cast<PropertyType_EightBytesOfData *>(m_rgData[i])->data();

      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      FileTime time;
      bytes >> time;
      xmlWriter.writeCharacters(
          time.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::AuthorOriginal: {
      xmlWriter.writeStartElement("AuthorOriginal");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::AuthorMostRecent: {
      xmlWriter.writeStartElement("AuthorMostRecent");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::LastModifiedTime: {
      xmlWriter.writeStartElement("LastModifiedTime");
      auto body =
          static_cast<PropertyType_EightBytesOfData *>(m_rgData[i])->data();

      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      Time32 time;
      bytes >> time;
      xmlWriter.writeCharacters(
          time.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsConflictPage: {
      xmlWriter.writeStartElement("IsConflictPage");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }

    /// \todo test TableColumnsLocked whether it produces correct output
    case PropertyIDs::TableColumnsLocked: {
      const auto data =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i])
              ->data();

      quint8 cColumns = data.at(0);
      quint8 nbytes = data.size() - 1;

      xmlWriter.writeStartElement("TableColumnsLocked");
      xmlWriter.writeAttribute("cColumns", QString::number(cColumns));

      xmlWriter.writeStartElement("rgfColumnLocked");
      xmlWriter.writeCharacters("{");
      quint8 kColumns = 0;
      for (quint8 j = 1; j < nbytes; j++) {
        quint8 chunk = data.at(j);
        for (size_t k = 0; k < 8; k++) {
          xmlWriter.writeCharacters(QString::number(((chunk >> k) & 0x1)));
          kColumns++;

          if (j + 1 != cColumns) {
            xmlWriter.writeCharacters(", ");
          } else {
            break;
          }
        }
      }
      xmlWriter.writeCharacters("}");
      xmlWriter.writeEndElement();

      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::SchemaRevisionInOrderToRead: {
      xmlWriter.writeStartElement("SchemaRevisionInOrderToRead");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(qStringHex(val, 8));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::IsConflictObjectForRender: {
      xmlWriter.writeStartElement("IsConflictObjectForRender");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
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
    case PropertyIDs::ConflictingUserName: {
      xmlWriter.writeStartElement("ConflictingUserName");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QString string = QString::fromUtf8(body->data().constData(), body->cb());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
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
    case PropertyIDs::IsConflictObjectForSelection: {
      xmlWriter.writeStartElement("IsConflictObjectForSelection");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PageLevel: {
      xmlWriter.writeStartElement("PageLevel");
      auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      qint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::TextRunIndex: {
      const auto data =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i])
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);

      QString indices = "";
      while (!bytes.atEnd()) {
        quint32 val;
        bytes >> val;

        indices += QString::number(val) + ", ";
      }
      // remove last ", " characters
      indices.resize(indices.size() - 2);

      xmlWriter.writeStartElement("TextRunIndex");
      xmlWriter.writeCharacters("{");
      xmlWriter.writeCharacters(indices);
      xmlWriter.writeCharacters("}");
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::TextRunFormatting:
      //      m_id_string = "TextRunFormatting";
      //      break;
    case PropertyIDs::Hyperlink: {
      xmlWriter.writeStartElement("Hyperlink");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::UnderlineType: {
      const auto data =
          static_cast<PropertyType_OneByteOfData *>(m_rgData[i])->data();
      quint8 val = data.toUInt();
      xmlWriter.writeStartElement("UnderlineType");
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::Hidden: {
      xmlWriter.writeStartElement("Hidden");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::HyperlinkProtected: {
      xmlWriter.writeStartElement("HyperlinkProtected");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::TextRunIsEmbeddedObject: {
      xmlWriter.writeStartElement("TextRunIsEmbeddedObject");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ImageAltText: {
      xmlWriter.writeStartElement("ImageAltText");
      const auto data =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i])
              ->data();
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort *>(data.constData()));

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::MathFormatting: {
      xmlWriter.writeStartElement("MathFormatting");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::ParagraphStyle: {
      //      break;
      //    }
    case PropertyIDs::ParagraphSpaceBefore: {
      xmlWriter.writeStartElement("ParagraphSpaceBefore");
      auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ParagraphSpaceAfter: {
      xmlWriter.writeStartElement("ParagraphSpaceBefore");
      auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ParagraphLineSpacingExact: {
      xmlWriter.writeStartElement("ParagraphLineSpacingExact");
      auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
      //          case PropertyIDs::MetaDataObjectsAboveGraphSpace: {

      ////        QUuid salt ( 0x22a8c031, 0x3600, 0x42ee, 0xb7, 0x14, 0xd7,
      /// 0xac, 0xda, 0x24, 0x35, 0xe8);

      //            break;
      //      }
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
    case PropertyIDs::HasVersionPages: {
      xmlWriter.writeStartElement("HasVersionPages");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ActionItemType: {

      if (m_rgPrids[i].type() ==
          PropertyIDType::FourBytesOfLengthFollowedByData) {
        auto data =
            static_cast<PropertyType_TwoBytesOfData *>(m_rgData[i])->data();
        QDataStream ds(data);
        quint16 val;
        ds >> val;

        xmlWriter.writeStartElement("ActionItemType");
        xmlWriter.writeAttribute("val", QString::number(val));

        if (val < 100) {
          xmlWriter.writeCharacters("Tag: " + QString::number(val));
        } else {
          switch (val) {
          case 100:
            xmlWriter.writeCharacters("Due today");
            break;
          case 101:
            xmlWriter.writeCharacters("Due tomorrow");
            break;
          case 102:
            xmlWriter.writeCharacters("Due this week");
            break;
          case 103:
            xmlWriter.writeCharacters("Due next week");
            break;
          case 104:
            xmlWriter.writeCharacters("No due date");
            break;
          case 105:
            xmlWriter.writeCharacters("Due on a custom date");
            break;
          }
        }
        xmlWriter.writeEndElement();
        break;
      }
    case PropertyIDs::NoteTagShape: {
      const auto data =
          static_cast<PropertyType_TwoBytesOfData *>(m_rgData[i])->data();

      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      NoteTagShape shape;
      bytes >> shape;
      xmlWriter << shape;
      break;
    }
    case PropertyIDs::NoteTagHighlightColor: {
      xmlWriter.writeStartElement("NoteTagHighlightColor");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      ColorRef val;
      bytes >> val;
      xmlWriter << val;
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::NoteTagTextColor: {
      xmlWriter.writeStartElement("NoteTagTextColor");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      ColorRef val;
      bytes >> val;
      xmlWriter << val;
      xmlWriter.writeEndElement();
      break;
    }

    /// \todo use proper BitReader
    case PropertyIDs::NoteTagPropertyStatus: {
      xmlWriter.writeStartElement("NoteTagPropertyStatus");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      quint32 val;
      bytes >> val;

      xmlWriter.writeStartElement("hasLabel");
      xmlWriter.writeCharacters((val & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("hasFontColor");
      xmlWriter.writeCharacters(((val >> 1) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("hasHighlightColor");
      xmlWriter.writeCharacters(((val >> 2) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("hasIcon");
      xmlWriter.writeCharacters(((val >> 3) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("DueToday");
      xmlWriter.writeCharacters(((val >> 6) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("DueTomorrow");
      xmlWriter.writeCharacters(((val >> 7) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("DueThisWeek");
      xmlWriter.writeCharacters(((val >> 8) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("DueNextWeek");
      xmlWriter.writeCharacters(((val >> 9) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("DueLater");
      xmlWriter.writeCharacters(((val >> 10) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("DueCustom");
      xmlWriter.writeCharacters(((val >> 11) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();

      xmlWriter.writeEndElement();
      break;
    }

    /// \todo not sure whether this is the correct string format (utf8/utf16)
    case PropertyIDs::NoteTagLabel: {
      xmlWriter.writeStartElement("wz");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QString string = QString::fromUtf8(body->data().constData(), body->cb());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::NoteTagCreated: {
      xmlWriter.writeStartElement("NoteTagCreated");
      auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();

      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      Time32 time;
      bytes >> time;
      xmlWriter.writeCharacters(
          time.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::NoteTagCompleted: {
      xmlWriter.writeStartElement("NoteTagCompleted");
      auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();

      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      Time32 time;
      bytes >> time;
      xmlWriter.writeCharacters(
          time.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::NoteTagDefinitionOid:
      //      m_id_string = "NoteTagDefinitionOid";
      //      break;
      //    case PropertyIDs::NoteTagStates:
      //      m_id_string = "NoteTagStates";
      //      break;
    case PropertyIDs::ActionItemStatus: {
      xmlWriter.writeStartElement("ActionItemStatus");
      const auto data =
          static_cast<PropertyType_TwoBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      quint16 val;
      bytes >> val;

      xmlWriter.writeStartElement("Completed");
      xmlWriter.writeCharacters((val & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("Disabled");
      xmlWriter.writeCharacters(((val >> 1) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("TaskTag");
      xmlWriter.writeCharacters(((val >> 2) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("Unsynchronized");
      xmlWriter.writeCharacters(((val >> 3) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("Removed");
      xmlWriter.writeCharacters(((val >> 4) & 0x1) == 1 ? "True" : "False");
      xmlWriter.writeEndElement();

      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::ActionItemSchemaVersion: {
      xmlWriter.writeStartElement("ActionItemSchemaVersion");
      const auto data =
          static_cast<PropertyType_OneByteOfData *>(m_rgData[i])->data();
      xmlWriter.writeCharacters("0x" + data.toHex());
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::ReadingOrderRTL: {
      xmlWriter.writeStartElement("ReadingOrderRTL");

      int val = m_rgPrids[i].boolValue();
      xmlWriter.writeCharacters(val == 0 ? "False"
                                         : (val == 1 ? "True" : "n.a."));
      xmlWriter.writeEndElement();
      break;
    }
      /// \todo declare ParagraphAlignment Enum
    case PropertyIDs::ParagraphAlignment: {

      const auto data =
          static_cast<PropertyType_OneByteOfData *>(m_rgData[i])->data();

      QString align;

      switch (data.toUInt()) {
      case 0:
        align = "Left";
        break;
      case 1:
        align = "Center";
        break;
      case 2:
        align = "Right";
        break;

      default:
        align = "invalid";
        break;
      }
      xmlWriter.writeStartElement("ParagraphAlignment");
      xmlWriter.writeCharacters(align);
      xmlWriter.writeEndElement();

      break;
    }
      //    case PropertyIDs::VersionHistoryGraphSpaceContextNodes:
      //      m_id_string = "VersionHistoryGraphSpaceContextNodes";
      //      break;
    case PropertyIDs::DisplayedPageNumber: {
      xmlWriter.writeStartElement("DisplayedPageNumber");
      const auto data =
          static_cast<PropertyType_OneByteOfData *>(m_rgData[i])->data();
      xmlWriter.writeCharacters(QString::number(data.toUInt()));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::SectionDisplayName: {
      xmlWriter.writeStartElement("wz");
      const auto body =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i]);
      QString string = QString::fromUtf8(body->data().constData(), body->cb());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::NextStyle: {
      xmlWriter.writeStartElement("wz");
      const auto body =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i]);
      QString string = QString::fromUtf8(body->data().constData(), body->cb());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
      //    case PropertyIDs::WebPictureContainer14:
      //      m_id_string = "WebPictureContainer14";
      //      break;
    case PropertyIDs::ImageUploadState: {

      const auto data =
          static_cast<PropertyType_OneByteOfData *>(m_rgData[i])->data();

      QString state;
      switch (data.toUInt()) {
      case 0:
        state = "Upload complete";
        break;
      case 1:
        state = "Upload in progress";
        break;
      case 2:
        state = "Upload failed";
        break;

      default:
        state = "Invalid Upload state";
        break;
      }
      xmlWriter.writeStartElement("ImageUploadState");
      xmlWriter.writeCharacters(state);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::TextExtendedAscii: {
      xmlWriter.writeStartElement("String");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);
      QString string = QString::fromUtf8(body->data().constData(), body->cb());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PictureWidth: {
      xmlWriter.writeStartElement("PictureWidth");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::PictureHeight: {
      xmlWriter.writeStartElement("PictureHeight");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float val;
      bytes >> val;
      xmlWriter.writeCharacters(QString::number(val, 'f', 5));
      xmlWriter.writeEndElement();
      break;
    }
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
    case PropertyIDs::WzHyperlinkUrl: {
      xmlWriter.writeStartElement("wz");
      const auto data =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i])
              ->data();
      QString string = QString::fromUtf8(data.constData(), data.size());
      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::TaskTagDueDate: {
      xmlWriter.writeStartElement("TaskTagDueDate");
      auto body =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();

      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      Time32 time;
      bytes >> time;
      xmlWriter.writeCharacters(
          time.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::undoc_AuthorInitials: {
      xmlWriter.writeStartElement("undoc_AuthorInitials");
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
    case PropertyIDs::undoc_ResolutionID: {
      xmlWriter.writeStartElement("undoc_ResolutionID");
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
    case PropertyIDs::undoc_StrokesBlob: {
      xmlWriter.writeStartElement("undoc_StrokesBlob");
      xmlWriter << *m_rgData[i];
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::undoc_StrokesIndex: {
      xmlWriter.writeStartElement("undoc_StrokesIndex");
      if (m_rgPrids[i].type() == PropertyIDType::FourBytesOfData) {
        auto body =
            static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
        QDataStream bytes(body);
        bytes.setByteOrder(QDataStream::LittleEndian);
        bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
        uint32_t val;
        bytes >> val;
        xmlWriter.writeCharacters(QString::number(val));
      }
      xmlWriter.writeEndElement();
      break;
    }
    case PropertyIDs::unodc_StrokeLanguage: {
      xmlWriter.writeStartElement("unodc_StrokeLanguage");
      const auto body =
          static_cast<PropertyType_TwoBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      LCID val;
      bytes >> val;
      xmlWriter.writeCharacters(val.toString());
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesColor: {
      xmlWriter.writeStartElement("undoc_StrokesColor");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();

      xmlWriter.writeCharacters("#" + data.toHex());
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesToolSizeHeight: {
      xmlWriter.writeStartElement("undoc_StrokesToolSizeHeight");
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
    case PropertyIDs::undoc_StrokesToolSizeWidth: {
      xmlWriter.writeStartElement("undoc_StrokesToolSizeWidth");
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

    case PropertyIDs::undoc_StrokesCreationTime: {
      xmlWriter.writeStartElement("undoc_StrokesCreationTime");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
                      m_rgData[i])
                      ->data();

      QDataStream bytes(body);
      bytes.setByteOrder(QDataStream::LittleEndian);
      FileTime time;
      bytes >> time;
      xmlWriter.writeCharacters(
          time.getTime().toString("dd/MM/yyyy hh:mm:ss AP"));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesRecognizedText: {
      xmlWriter.writeStartElement("undoc_StrokesRecognizedText");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);

      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort *>(body->data().constData()),
          body->cb() / 2);
      QStringList strings = string.split('\0');
      for (const auto &str : strings) {
        if (str.size() > 0) {
          xmlWriter.writeStartElement("match");
          xmlWriter.writeCharacters(str);
          xmlWriter.writeEndElement();
        }
      }
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesOffsetsVertHoriz: {
      xmlWriter.writeStartElement("undoc_StrokesOffsetsVertHoriz");
      const auto data =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i])
              ->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      bytes.setFloatingPointPrecision(QDataStream::SinglePrecision);
      float vert, horiz;
      bytes >> vert;
      bytes >> horiz;

      xmlWriter.writeStartElement("Vert");
      xmlWriter.writeCharacters(QString::number(vert, 'f', 5));
      xmlWriter.writeEndElement();
      xmlWriter.writeStartElement("Horiz");
      xmlWriter.writeCharacters(QString::number(horiz, 'f', 5));
      xmlWriter.writeEndElement();

      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesModus: {
      xmlWriter.writeStartElement("undoc_StrokesModus");
      const auto data =
          static_cast<PropertyType_OneByteOfData *>(m_rgData[i])->data();
      switch (data.toInt()) {
      case 0:
        xmlWriter.writeCharacters("HandwrittingAndDrawing");
        break;
      case 1:
        xmlWriter.writeCharacters("DrawingOnly");
        break;
      case 2:
        xmlWriter.writeCharacters("HandwritingOnly");
        break;
      default:
        break;
      }

      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_StrokesGUID: {
      xmlWriter.writeStartElement("undoc_StrokesGUID");
      const auto data =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i])
              ->data();
      QDataStream bytes(data);
      QUuid guid;
      bytes >> guid;

      xmlWriter.writeCharacters(guid.toString());
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_RecognizedText: {
      xmlWriter.writeStartElement("undoc_RecognizedText");
      auto body = static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
          m_rgData[i]);

      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort *>(body->data().constData()),
          body->cb() / 2);
      QStringList strings = string.split('\0');
      for (const auto &str : strings) {
        if (str.size() > 0) {
          xmlWriter.writeStartElement("match");
          xmlWriter.writeCharacters(str);
          xmlWriter.writeEndElement();
        }
      }
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_tocSectionName: {
      xmlWriter.writeStartElement("undoc_tocSectionName");
      const auto body =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i]);
      QString string = QString::fromUtf16(
          reinterpret_cast<const ushort *>(body->data().constData()),
          body->cb() / 2);

      xmlWriter.writeCharacters(string);
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_tocSectionIndex: {
      xmlWriter.writeStartElement("undoc_tocSectionIndex");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;

      xmlWriter.writeCharacters(QString::number(val));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_tocSectionGUID: {
      xmlWriter.writeStartElement("undoc_tocSectionGUID");
      const auto data =
          static_cast<PropertyType_FourBytesOfLengthFollowedByData *>(
              m_rgData[i])
              ->data();
      QDataStream bytes(data);
      QUuid val;
      bytes >> val;
      xmlWriter.writeCharacters(val.toString());
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_tocSectionColor: {
      xmlWriter.writeStartElement("undoc_tocSectionColor");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      ColorRef val;
      bytes >> val;
      xmlWriter << val;
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_SchemaRevisionInOrderToRead: {
      xmlWriter.writeStartElement("undoc_SchemaRevisionInOrderToRead");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();
      QDataStream bytes(data);
      bytes.setByteOrder(QDataStream::LittleEndian);
      quint32 val;
      bytes >> val;
      xmlWriter.writeCharacters(qStringHex(val, 8));
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::undoc_PageBackgroundColor: {
      xmlWriter.writeStartElement("undoc_PageBackgroundColor");
      const auto data =
          static_cast<PropertyType_FourBytesOfData *>(m_rgData[i])->data();

      xmlWriter.writeCharacters("#" + data.toHex());
      xmlWriter.writeEndElement();
      break;
    }

    case PropertyIDs::None:
    default:
      xmlWriter << *m_rgData[i];
      break;
    }
    }
    xmlWriter.writeEndElement(); // PropertyID
  }

  xmlWriter.writeEndElement(); // PropertySet
}

} // namespace MSONcommon
