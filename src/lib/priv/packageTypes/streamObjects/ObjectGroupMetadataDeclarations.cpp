#include "ObjectGroupMetadataDeclarations.h"

#include <numeric>

namespace libmson {
namespace packStore {
namespace streamObj {
ObjectGroupMetadataDeclarations::ObjectGroupMetadataDeclarations() {}


std::vector<ObjectGroupMetadata_SPtr_t>
ObjectGroupMetadataDeclarations::getMetaData() const
{
  return m_metaData;
}

void ObjectGroupMetadataDeclarations::setMetaData(
    const std::vector<ObjectGroupMetadata_SPtr_t>& metaData)
{
  m_metaData = metaData;
}


void ObjectGroupMetadataDeclarations::deserialize(QDataStream& ds)
{
  auto header = std::make_shared<StreamObjectHeader>();
  ds >> *header;

  if (header->getType() != getType()) {
    qFatal("Trying to deserialze StreamObject of incorrect header type "
           "(ObjectGroupMetadataDeclarations)");
  }

  qint64 origPos = ds.device()->pos();

  char peek[1];
  qint64 peeking = ds.device()->peek(peek, 1);
  if (peeking < 1) {
    qFatal("Error reading bytes during deserialize RevisionManifest");
  }

  while (((static_cast<uint8_t>(peek[0]) & 0x1) != 1)) {
    ds.startTransaction();

    auto strmObjHeader = std::make_shared<StreamObjectHeader>();
    ds >> *strmObjHeader;

    ds.rollbackTransaction();


    if (strmObjHeader->getType() == StreamObjectType::ObjectGroupMetadata) {
      auto strmObj = std::make_shared<streamObj::ObjectGroupMetadata>();
      ds >> *strmObj;

      m_metaData.push_back(strmObj);
    }

    ds.device()->peek(peek, 1);
  }

  if ((origPos + header->getLength()) != (quint64)ds.device()->pos()) {
    qFatal("Something went wrong parsing ObjectGroupObjectDeclare");
  }

  StreamObjectHeaderEnd end(header);
  ds << end;
}

void ObjectGroupMetadataDeclarations::serialize(QDataStream& ds) const
{
  auto header = std::make_shared<StreamObjectHeader>(getType(), body_cb());

  ds << *header;

  for (const auto& entry : m_metaData) {
    ds << *std::dynamic_pointer_cast<ObjectGroupMetadata>(entry);
  }

  StreamObjectHeaderEnd end(header);
  ds << end;
}

quint64 ObjectGroupMetadataDeclarations::body_cb() const
{
  return std::accumulate(
      m_metaData.begin(), m_metaData.end(),
      StreamObjectHeaderEnd::getSizeInFile(getType()),
      [](quint64 sub, const StreamObject_SPtr_t& entry) {
        return sub + entry->getSizeInFile();
      });
}

StreamObjectType ObjectGroupMetadataDeclarations::getType() const
{
  return StreamObjectType::ObjectGroupMetadataDeclarations;
}
} // namespace streamObj
} // namespace packStore
} // namespace libmson
