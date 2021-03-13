#include "StreamObjectTypes.h"

QString libmson::fsshttpb::streamObjectTypeToString(const libmson::fsshttpb::StreamObjectType& type)
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
