#include "RevisionManifestRootDeclare.h"
namespace libmson {
namespace packStore {
namespace streamObj {
RevisionManifestRootDeclare::RevisionManifestRootDeclare() {}

CompactExtGuid RevisionManifestRootDeclare::getRoot() const { return m_root; }

void RevisionManifestRootDeclare::setRoot(const CompactExtGuid& root)
{
  m_root = root;
}

CompactExtGuid RevisionManifestRootDeclare::getObject() const
{
  return m_object;
}

void RevisionManifestRootDeclare::setObject(const CompactExtGuid& object)
{
  m_object = object;
}



void RevisionManifestRootDeclare::deserialize(QDataStream& ds)
{
  StreamObjectHeader header;
  ds >> header;

  if (header.getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(RevisionManifestRootDeclare)");
  }

  qint64 origPos = ds.device()->pos();

  ds >> m_root;
  ds >> m_object;

  if ((origPos + header.getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing RevisionManifestRootDeclare");
  }
}

void RevisionManifestRootDeclare::serialize(QDataStream& ds) const
{
  StreamObjectHeader header(getType(), body_cb());

  ds << header;
  ds << m_root;
  ds << m_object;
}

quint64 RevisionManifestRootDeclare::body_cb() const
{
  return m_root.getSizeInFile() + m_object.getSizeInFile();
}

StreamObjectType RevisionManifestRootDeclare::getType() const
{
  return StreamObjectType::RevisionManifestRootDeclare;
}

} // namespace streamObj
} // namespace packStore
} // namespace libmson
