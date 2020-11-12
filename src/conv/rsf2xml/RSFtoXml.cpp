#include "RSFtoXml.h"

#include "../../lib/priv/utils/Helper.h"

#include <QXmlStreamWriter>

QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const ChunkTerminatorFND& fnd)
{
  xmlWriter.writeStartElement("ChunkTerminatorFND");
  xmlWriter.writeEndElement();
}

QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const DataSignatureGroupDefinitionFND& fnd)
{
  xmlWriter.writeStartElement("DataSignatureGroupDefinitionFND");

  xmlWriter.writeAttribute("dataSignatureGroup", fnd.dataSignatureGroup().toString());
  xmlWriter.writeEndElement();
}

// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const FileDataStoreListReferenceFND& fnd) {
//  xmlWriter.writeStartElement("FileDataStoreListReferenceFND");
//  xmlWriter << fnd.getRef();

//  xmlWriter << fnd.m_StoreList;
//  xmlWriter.writeEndElement();
//}

QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, ObjectDeclaration2RefCountFND& fnd)
{
  xmlWriter.writeStartElement("ObjectDeclaration2RefCountFND");

  xmlWriter << fnd.getBlobRef();

  xmlWriter << fnd.getBody();

  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(qStringHex(fnd.getCRef(), 8)) xmlWriter.writeEndElement();

  xmlWriter << fnd.getPropSet();

  xmlWriter.writeEndElement();
}


QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, ObjectDeclaration2LargeRefCountFND& fnd)
{

  xmlWriter.writeStartElement("ObjectDeclaration2LargeRefCountFND");

  xmlWriter << fnd.getBlobRef();
  xmlWriter << fnd.getBody();
  xmlWriter.writeStartElement("cRef");
  xmlWriter.writeCharacters(qStringHex(fnd.getCRef(), 8)) xmlWriter.writeEndElement();
  xmlWriter << fnd.getPropSet();

  xmlWriter.writeEndElement();
}


QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const ObjectDataEncryptionKeyV2FNDX& fnd)
{
  xmlWriter.writeStartElement("ObjectDataEncryptionKeyV2FNDX");

  xmlWriter << fnd.m_blobRef;

  xmlWriter << fnd.getEncryptionData();


  xmlWriter.writeEndElement();
}
QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, ObjectSpaceObjectPropSet& obj)
{
  xmlWriter.writeStartElement("ObjectSpaceObjectPropSet");
  xmlWriter.writeAttribute("paddingLength", QString::number(obj.getPaddingLength()));

  xmlWriter.writeStartElement("ObjectSpaceObjectStreamOfOIDs");
  if (obj.OIDs().header().count() > 0) {
    xmlWriter << obj.OIDs();
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ObjectSpaceObjectStreamOfOSIDs");
  if (obj.OSIDs().header().count() > 0) {
    xmlWriter << obj.OSIDs();
  }
  xmlWriter.writeEndElement();

  xmlWriter.writeStartElement("ObjectSpaceObjectStreamOfContextIDs");
  if (obj.getContextIDs().header().count() > 0) {
    xmlWriter << obj.getContextIDs();
  }
}
xmlWriter.writeEndElement();

xmlWriter << obj.getBody();

xmlWriter.writeEndElement();
}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}
// QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const PLACEHOLDER& fnd) {}


QXmlStreamWriter& operator<<(QXmlStreamWriter& xmlWriter, const RSChunkContainer_SPtr_t& obj)
{

  //  switch (obj->getType()) {
  ////  case RevisionStoreChunkType::
  //  }

  /// \todo needs a large switch to cast into chunkables and use sub operator
}


// xmlWriter.writeStartElement("FileDataStoreListReferenceFND");
// xmlWriter << m_ref;

// xmlWriter << m_StoreList;
// xmlWriter.writeEndElement();
