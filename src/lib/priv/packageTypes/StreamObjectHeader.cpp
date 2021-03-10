#include "StreamObjectHeader.h"

#include "StreamObjectHeaderEnd.h"
#include "../commonTypes/CompactUInt64.h"

#include <QDebug>

namespace libmson {
namespace packStore {

StreamObjectHeader::StreamObjectHeader()
    : m_type(StreamObjectType::Invalid), m_length()
{
}
StreamObjectHeader::StreamObjectHeader(
    const StreamObjectType& type, const uint64_t& length)
    : m_type(type), m_length(length)
{
}

StreamObjectType StreamObjectHeader::getType() const { return m_type; }

void StreamObjectHeader::setType(const StreamObjectType& type)
{
  m_type = type;
}

uint64_t StreamObjectHeader::getLength() const { return m_length; }

void StreamObjectHeader::setLength(const uint64_t& length)
{
  m_length = length;
}

std::shared_ptr<StreamObjectHeaderEnd> StreamObjectHeader::getEnd() const
{
  return m_end;
}

void StreamObjectHeader::setEnd(
    const std::shared_ptr<StreamObjectHeaderEnd>& end)
{
  m_end = end;
}

quint64 StreamObjectHeader::getSizeInFile() const
{
  uint16_t typeBits = static_cast<uint16_t>(m_type);
  if (m_length < 127 && (typeBits >> 6) == 0) {
    return 2;
  }
  else {
    return 4;
  }
}

quint64 StreamObjectHeader::getSizeInFile(
    const quint64& length, const StreamObjectType& type)
{
  uint16_t typeBits = static_cast<uint16_t>(type);
  if (length < 127 && (typeBits >> 6) == 0) {
    return 2;
  }
  else {
    return 4;
  }
}

QString StreamObjectHeader::typeToString(const StreamObjectType& type)
{
  switch (type) {
  case StreamObjectType::DataElement:
    return "DataElement";

  case StreamObjectType::ObjectDataBLOB:
    return "ObjectDataBLOB";

  case StreamObjectType::ObjectGroupObjectExcludedData:
    return "ObjectGroupObjectExcludedData";

  case StreamObjectType::WaterlineKnowledgeEntry:
    return "WaterlineKnowledgeEntry";

  case StreamObjectType::ObjectGroupObjectDataBLOBDeclaration:
    return "ObjectGroupObjectDataBLOBDeclaration";

  case StreamObjectType::DataElementHash:
    return "DataElementHash";

  case StreamObjectType::StorageManifestRootDeclare:
    return "StorageManifestRootDeclare";

  case StreamObjectType::RevisionManifestRootDeclare:
    return "RevisionManifestRootDeclare";

  case StreamObjectType::CellManifestCurrentRevision:
    return "CellManifestCurrentRevision";

  case StreamObjectType::StorageManifestSchemaGUID:
    return "StorageManifestSchemaGUID";

  case StreamObjectType::StorageIndexRevisionMapping:
    return "StorageIndexRevisionMapping";

  case StreamObjectType::StorageIndexCellMapping:
    return "StorageIndexCellMapping";

  case StreamObjectType::CellKnowledgeRange:
    return "CellKnowledgeRange";

  case StreamObjectType::Knowledge:
    return "Knowledge";

  case StreamObjectType::StorageIndexManifestMapping:
    return "StorageIndexManifestMapping";

  case StreamObjectType::CellKnowledge:
    return "CellKnowledge";

  case StreamObjectType::DataElementPackage:
    return "DataElementPackage";

  case StreamObjectType::ObjectGroupObjectData:
    return "ObjectGroupObjectData";

  case StreamObjectType::CellKnowledgeEntry:
    return "CellKnowledgeEntry";

  case StreamObjectType::ObjectGroupObjectDeclare:
    return "ObjectGroupObjectDeclare";

  case StreamObjectType::RevisionManifestObjectGroupReference:
    return "RevisionManifestObjectGroupReference";

  case StreamObjectType::RevisionManifest:
    return "RevisionManifest";

  case StreamObjectType::ObjectGroupObjectDataBLOBReference:
    return "ObjectGroupObjectDataBLOBReference";

  case StreamObjectType::ObjectGroupDeclarations:
    return "ObjectGroupDeclarations";

  case StreamObjectType::ObjectGroupData:
    return "ObjectGroupData";

  case StreamObjectType::WaterlineKnowledge:
    return "WaterlineKnowledge";

  case StreamObjectType::ContentTagKnowledge:
    return "ContentTagKnowledge";

  case StreamObjectType::ContentTagKnowledgeEntry:
    return "ContentTagKnowledgeEntry";

  case StreamObjectType::QueryChangesVersioning:
    return "QueryChangesVersioning";

    /* 32bit header types */
  case StreamObjectType::Request:
    return "Request";

  case StreamObjectType::Subresponse:
    return "Subresponse";

  case StreamObjectType::Subrequest:
    return "Subrequest";

  case StreamObjectType::ReadAccessResponse:
    return "ReadAccessResponse";

  case StreamObjectType::SpecializedKnowledge:
    return "SpecializedKnowledge";

  case StreamObjectType::WriteAccessResponse:
    return "WriteAccessResponse";

  case StreamObjectType::QueryChangesFilter:
    return "QueryChangesFilter";

  case StreamObjectType::ErrorWin32:
    return "ErrorWin32";

  case StreamObjectType::ErrorProtocol:
    return "ErrorProtocol";

  case StreamObjectType::Error:
    return "Error";

  case StreamObjectType::ErrorStringSupplementalInfo:
    return "ErrorStringSupplementalInfo";

  case StreamObjectType::UserAgentVersion:
    return "UserAgentVersion";

  case StreamObjectType::QueryChangesFilterSchemaSpecific:
    return "QueryChangesFilterSchemaSpecific";

  case StreamObjectType::QueryChangesRequest:
    return "QueryChangesRequest";

  case StreamObjectType::ErrorHRESULT:
    return "ErrorHRESULT";

  case StreamObjectType::QueryChangesFilterDataElementIDs:
    return "QueryChangesFilterDataElementIDs";

  case StreamObjectType::UserAgentGUID:
    return "UserAgentGUID";

  case StreamObjectType::QueryChangesFilterDataElementType:
    return "QueryChangesFilterDataElementType";

  case StreamObjectType::QueryChangesDataConstraint:
    return "QueryChangesDataConstraint";

  case StreamObjectType::PutChangesRequest:
    return "PutChangesRequest";

  case StreamObjectType::QueryChangesRequestArguments:
    return "QueryChangesRequestArguments";

  case StreamObjectType::QueryChangesFilterCellID:
    return "QueryChangesFilterCellID";

  case StreamObjectType::UserAgent:
    return "UserAgent";

  case StreamObjectType::QueryChangesResponse:
    return "QueryChangesResponse";

  case StreamObjectType::QueryChangesFilterHierarchy:
    return "QueryChangesFilterHierarchy";

  case StreamObjectType::Response:
    return "Response";

  case StreamObjectType::ErrorCell:
    return "ErrorCell";

  case StreamObjectType::QueryChangesFilterFlags:
    return "QueryChangesFilterFlags";

  case StreamObjectType::DataElementFragment:
    return "DataElementFragment";

  case StreamObjectType::FragmentKnowledge:
    return "FragmentKnowledge";

  case StreamObjectType::FragmentKnowledgeEntry:
    return "FragmentKnowledgeEntry";

  case StreamObjectType::ObjectGroupMetadata:
    return "ObjectGroupMetadata";

  case StreamObjectType::ObjectGroupMetadataDeclarations:
    return "ObjectGroupMetadataDeclarations";

  case StreamObjectType::ONPackageStart:
    return "ONPackageStart";

  case StreamObjectType::AllocateExtendedGUIDRangeRequest:
    return "AllocateExtendedGUIDRangeRequest";

  case StreamObjectType::AllocateExtendedGUIDRangeResponse:
    return "AllocateExtendedGUIDRangeResponse";

  case StreamObjectType::TargetPartitionId:
    return "TargetPartitionId";

  case StreamObjectType::PutChangesLockId:
    return "PutChangesLockId";

  case StreamObjectType::AdditionalFlags:
    return "AdditionalFlags";

  case StreamObjectType::PutChangesResponse:
    return "PutChangesResponse";

  case StreamObjectType::RequestHashingOptions:
    return "RequestHashingOptions";

  case StreamObjectType::DiagnosticRequestOptionOutput:
    return "DiagnosticRequestOptionOutput";

  case StreamObjectType::DiagnosticRequestOptionInput:
    return "DiagnosticRequestOptionInput";

  case StreamObjectType::UserAgentClientAndPlatform:
    return "UserAgentClientAndPlatform";

  case StreamObjectType::VersionTokenKnowledge:
    return "VersionTokenKnowledge";

  case StreamObjectType::CellRoundtripOptions:
    return "CellRoundtripOptions";

  case StreamObjectType::FileHash:
    return "FileHash";

  case StreamObjectType::Invalid:
  default:
    return QString::number(static_cast<uint16_t>(type), 16);
  }
}


void StreamObjectHeader::deserialize(QDataStream& ds)
{

  uint16_t composite;
  ds >> composite;

  /*16 bit header*/
  if ((composite & 0x3) == 0) {
    uint8_t typeVal = (composite >> 3) & 0x3F;

    if (validStreamObjectTypeValues.find(typeVal) !=
        validStreamObjectTypeValues.end()) {
      m_type = static_cast<StreamObjectType>(typeVal);
    }
    else {
      qDebug() << "TypeVal: " << QString::number(typeVal);
      qFatal("Incorrectly formated Stream Object Header (type)");
    }
    // test if compound bit is correct
    if (((composite >> 2) & 0x1) != compoundType.at(m_type)) {
      qFatal("Incorrectlyformated Stream Object Header (compound bit)");
    }

    m_length = (composite >> 9) & 0x7F;
  }
  /* 32 bit header */
  else if ((composite & 0x3) == 2) {

    uint16_t highBytes;
    ds >> highBytes;

    uint16_t typeVal = ((highBytes & 0x1) << 13) + ((composite >> 3) & 0x1FFF);
    if (validStreamObjectTypeValues.find(typeVal) !=
        validStreamObjectTypeValues.end()) {
      m_type = static_cast<StreamObjectType>(typeVal);
    }
    else {
      qDebug() << "TypeVal: " << QString::number(typeVal);
      qFatal("Incorrectly formated Stream Object Header (type)");
    }
    // test if compound bit is correct
    if (((composite >> 2) & 0x1) != compoundType.at(m_type)) {
      qFatal("Incorrectly formated Stream Object Header (compound bit)");
    }


    uint16_t subtotal = highBytes >> 1;

    if (subtotal == 0x7FFF) {
      /* large length */

      CompactUInt64 total;
      ds >> total;

      m_length = total.getValue();
    }
    else {
      m_length = subtotal;
    }
  }
  else {
    qDebug() << "Composite:" << composite;
    qWarning("Error: Incorrectly formated StreamObjectHeader");
  }
}

void StreamObjectHeader::serialize(QDataStream& ds) const
{

  uint16_t typeBits = static_cast<uint16_t>(m_type);
  if (m_length < 127 && (typeBits >> 6) == 0) {
    /*16 bit header*/
    typeBits <<= 3;

    typeBits += compoundType.at(m_type) << 2;

    typeBits += m_length << 9;

    ds << typeBits;
  }
  else {
    /* 32 bit header */
    uint32_t composite = 2;

    composite += compoundType.at(m_type) << 2;

    composite += typeBits << 3;
    if (m_length < 0x7FFF) {
      composite += m_length << 17;
      ds << composite;
    }
    else {
      composite += 0x7FFF << 17;
      ds << composite;

      CompactUInt64 large(m_length);
      ds << large;
    }
  }
}

} // namespace packStore
} // namespace libmson
