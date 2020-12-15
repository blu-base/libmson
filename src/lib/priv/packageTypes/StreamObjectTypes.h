#ifndef STREAMOBJECTTYPES_H
#define STREAMOBJECTTYPES_H

#include <cstdint>
#include <map>
#include <set>

namespace libmson {
namespace packStore {

enum class StreamObjectType : uint16_t {
  Invalid = 0,
  /* 16 bit header typers */
  DataElement                           = 0x01,
  ObjectDataBLOB                        = 0x02,
  ObjectGroupObjectExcludedData         = 0x03,
  WaterlineKnowledgeEntry               = 0x04,
  ObjectGroupObjectDataBLOBDeclaration  = 0x05,
  DataElementHash                       = 0x06,
  StorageManifestRootDeclare            = 0x07,
  RevisionManifestRootDeclare           = 0x00A,
  CellManifestCurrentRevision           = 0x00B,
  StorageManifestSchemaGUID             = 0x00C,
  StorageIndexRevisionMapping           = 0x00D,
  StorageIndexCellMapping               = 0x00E,
  CellKnowledgeRange                    = 0x00F,
  Knowledge                             = 0x010,
  StorageIndexManifestMapping           = 0x011,
  CellKnowledge                         = 0x014,
  DataElementPackage                    = 0x015,
  ObjectGroupObjectData                 = 0x016,
  CellKnowledgeEntry                    = 0x017,
  ObjectGroupObjectDeclare              = 0x018,
  RevisionManifestObjectGroupReferences = 0x019,
  RevisionManifest                      = 0x01A,
  ObjectGroupObjectDataBLOBReference    = 0x01C,
  ObjectGroupDeclarations               = 0x01D,
  ObjectGroupData                       = 0x01E,
  WaterlineKnowledge                    = 0x029,
  ContentTagKnowledge                   = 0x02D,
  ContentTagKnowledgeEntry              = 0x02E,
  QueryChangesVersioning                = 0x030,
  /* 32 bit header types */
  Request                           = 0x040,
  Subresponse                       = 0x041,
  Subrequest                        = 0x042,
  ReadAccessResponse                = 0x043,
  SpecializedKnowledge              = 0x044,
  WriteAccessResponse               = 0x046,
  QueryChangesFilter                = 0x047,
  ErrorWin32                        = 0x049,
  ErrorProtocol                     = 0x04B,
  Error                             = 0x04D,
  ErrorStringSupplementalInfo       = 0x04E,
  UserAgentVersion                  = 0x04F,
  QueryChangesFilterSchemaSpecific  = 0x050,
  QueryChangesRequest               = 0x051,
  ErrorHRESULT                      = 0x052,
  QueryChangesFilterDataElementIDs  = 0x054,
  UserAgentGUID                     = 0x055,
  QueryChangesFilterDataElementType = 0x057,
  QueryChangesDataConstraint        = 0x059,
  PutChangesRequest                 = 0x05A,
  QueryChangesRequestArguments      = 0x05B,
  QueryChangesFilterCellID          = 0x05C,
  UserAgent                         = 0x05D,
  QueryChangesResponse              = 0x05F,
  QueryChangesFilterHierarchy       = 0x060,
  Response                          = 0x062,
  ErrorCell                         = 0x066,
  QueryChangesFilterFlags           = 0x068,
  DataElementFragment               = 0x06A,
  FragmentKnowledge                 = 0x06B,
  FragmentKnowledgeEntry            = 0x06C,
  ObjectGroupMetadata               = 0x078,
  ObjectGroupMetadataDeclarations   = 0x079,
  ONPackageStart                    = 0x07A,
  AllocateExtendedGUIDRangeRequest  = 0x080,
  AllocateExtendedGUIDRangeResponse = 0x081,
  TargetPartitionId                 = 0x083,
  PutChangesLockId                  = 0x085,
  AdditionalFlags                   = 0x086,
  PutChangesResponse                = 0x087,
  RequestHashingOptions             = 0x088,
  DiagnosticRequestOptionOutput     = 0x089,
  DiagnosticRequestOptionInput      = 0x08A,
  UserAgentClientAndPlatform        = 0x08B,
  VersionTokenKnowledge             = 0x08C,
  CellRoundtripOptions              = 0x08D,
  FileHash                          = 0x08E,
};

const std::set<uint16_t> validStreamObjectTypeValues = {
    /* 16 bit header typers */
    0x01,  /* DataElement */
    0x02,  /* ObjectDataBLOB */
    0x03,  /* ObjectGroupObjectExcludedData */
    0x04,  /* WaterlineKnowledgeEntry */
    0x05,  /* ObjectGroupObjectDataBLOBDeclaration */
    0x06,  /* DataElementHash */
    0x07,  /* StorageManifestRootDeclare */
    0x00A, /* RevisionManifestRootDeclare */
    0x00B, /* CellManifestCurrentRevision */
    0x00C, /* StorageManifestSchemaGUID */
    0x00D, /* StorageIndexRevisionMapping */
    0x00E, /* StorageIndexCellMapping */
    0x00F, /* CellKnowledgeRange */
    0x010, /* Knowledge */
    0x011, /* StorageIndexManifestMapping */
    0x014, /* CellKnowledge */
    0x015, /* DataElementPackage */
    0x016, /* ObjectGroupObjectData */
    0x017, /* CellKnowledgeEntry */
    0x018, /* ObjectGroupObjectDeclare */
    0x019, /* RevisionManifestObjectGroupReferences */
    0x01A, /* RevisionManifest */
    0x01C, /* ObjectGroupObjectDataBLOBReference */
    0x01D, /* ObjectGroupDeclarations */
    0x01E, /* ObjectGroupData */
    0x029, /* WaterlineKnowledge */
    0x02D, /* ContentTagKnowledge */
    0x02E, /* ContentTagKnowledgeEntry */
    0x030, /* QueryChangesVersioning */
    /* 32 bit header types */
    0x040, /* Request */
    0x041, /* Subresponse */
    0x042, /* Subrequest */
    0x043, /* ReadAccessResponse */
    0x044, /* SpecializedKnowledge */
    0x046, /* WriteAccessResponse */
    0x047, /* QueryChangesFilter */
    0x049, /* ErrorWin32 */
    0x04B, /* ErrorProtocol */
    0x04D, /* Error */
    0x04E, /* ErrorStringSupplementalInfo */
    0x04F, /* UserAgentVersion */
    0x050, /* QueryChangesFilterSchemaSpecific */
    0x051, /* QueryChangesRequest */
    0x052, /* ErrorHRESULT */
    0x054, /* QueryChangesFilterDataElementIDs */
    0x055, /* UserAgentGUID */
    0x057, /* QueryChangesFilterDataElementType */
    0x059, /* QueryChangesDataConstraint */
    0x05A, /* PutChangesRequest */
    0x05B, /* QueryChangesRequestArguments */
    0x05C, /* QueryChangesFilterCellID */
    0x05D, /* UserAgent */
    0x05F, /* QueryChangesResponse */
    0x060, /* QueryChangesFilterHierarchy */
    0x062, /* Response */
    0x066, /* ErrorCell */
    0x068, /* QueryChangesFilterFlags */
    0x06A, /* DataElementFragment */
    0x06B, /* FragmentKnowledge */
    0x06C, /* FragmentKnowledgeEntry */
    0x078, /* ObjectGroupMetadata */
    0x079, /* ObjectGroupMetadataDeclarations */
    0x07A, /* ONPackageStart */
    0x080, /* AllocateExtendedGUIDRangeRequest */
    0x081, /* AllocateExtendedGUIDRangeResponse */
    0x083, /* TargetPartitionId */
    0x085, /* PutChangesLockId */
    0x086, /* AdditionalFlags */
    0x087, /* PutChangesResponse */
    0x088, /* RequestHashingOptions */
    0x089, /* DiagnosticRequestOptionOutput */
    0x08A, /* DiagnosticRequestOptionInput */
    0x08B, /* UserAgentClientAndPlatform */
    0x08C, /* VersionTokenKnowledge */
    0x08D, /* CellRoundtripOptions */
    0x08E, /* FileHash */
};

/** If compound type is 1, then a StreamObjectHeaderEnd must follow */
const std::map<StreamObjectType, uint8_t> compoundType = {
    {StreamObjectType::Invalid, 0},
    /* 16bit header typers */
    {StreamObjectType::DataElement, 1},
    {StreamObjectType::ObjectDataBLOB, 0},
    {StreamObjectType::ObjectGroupObjectExcludedData, 0},
    {StreamObjectType::WaterlineKnowledgeEntry, 0},
    {StreamObjectType::ObjectGroupObjectDataBLOBDeclaration, 0},
    {StreamObjectType::DataElementHash, 0},
    {StreamObjectType::StorageManifestRootDeclare, 0},
    {StreamObjectType::RevisionManifestRootDeclare, 0},
    {StreamObjectType::CellManifestCurrentRevision, 0},
    {StreamObjectType::StorageManifestSchemaGUID, 0},
    {StreamObjectType::StorageIndexRevisionMapping, 0},
    {StreamObjectType::StorageIndexCellMapping, 0},
    {StreamObjectType::CellKnowledgeRange, 0},
    {StreamObjectType::Knowledge, 1},
    {StreamObjectType::StorageIndexManifestMapping, 0},
    {StreamObjectType::CellKnowledge, 1},
    {StreamObjectType::DataElementPackage, 1},
    {StreamObjectType::ObjectGroupObjectData, 0},
    {StreamObjectType::CellKnowledgeEntry, 0},
    {StreamObjectType::ObjectGroupObjectDeclare, 0},
    {StreamObjectType::RevisionManifestObjectGroupReferences, 0},
    {StreamObjectType::RevisionManifest, 0},
    {StreamObjectType::ObjectGroupObjectDataBLOBReference, 0},
    {StreamObjectType::ObjectGroupDeclarations, 1},
    {StreamObjectType::ObjectGroupData, 1},
    {StreamObjectType::WaterlineKnowledge, 1},
    {StreamObjectType::ContentTagKnowledge, 1},
    {StreamObjectType::ContentTagKnowledgeEntry, 0},
    {StreamObjectType::QueryChangesVersioning, 0},
    /* 32bit header types */
    {StreamObjectType::Request, 1},
    {StreamObjectType::Subresponse, 1},
    {StreamObjectType::Subrequest, 1},
    {StreamObjectType::ReadAccessResponse, 1},
    {StreamObjectType::SpecializedKnowledge, 1},
    {StreamObjectType::WriteAccessResponse, 1},
    {StreamObjectType::QueryChangesFilter, 1},
    {StreamObjectType::ErrorWin32, 0},
    {StreamObjectType::ErrorProtocol, 0},
    {StreamObjectType::Error, 1},
    {StreamObjectType::ErrorStringSupplementalInfo, 0},
    {StreamObjectType::UserAgentVersion, 0},
    {StreamObjectType::QueryChangesFilterSchemaSpecific, 0},
    {StreamObjectType::QueryChangesRequest, 0},
    {StreamObjectType::ErrorHRESULT, 0},
    {StreamObjectType::QueryChangesFilterDataElementIDs, 0},
    {StreamObjectType::UserAgentGUID, 0},
    {StreamObjectType::QueryChangesFilterDataElementType, 0},
    {StreamObjectType::QueryChangesDataConstraint, 0},
    {StreamObjectType::PutChangesRequest, 0},
    {StreamObjectType::QueryChangesRequestArguments, 0},
    {StreamObjectType::QueryChangesFilterCellID, 0},
    {StreamObjectType::UserAgent, 1},
    {StreamObjectType::QueryChangesResponse, 0},
    {StreamObjectType::QueryChangesFilterHierarchy, 0},
    {StreamObjectType::Response, 1},
    {StreamObjectType::ErrorCell, 0},
    {StreamObjectType::QueryChangesFilterFlags, 0},
    {StreamObjectType::DataElementFragment, 0},
    {StreamObjectType::FragmentKnowledge, 1},
    {StreamObjectType::FragmentKnowledgeEntry, 0},
    {StreamObjectType::ObjectGroupMetadata, 0},
    {StreamObjectType::ObjectGroupMetadataDeclarations, 1},
    {StreamObjectType::ONPackageStart, 1},
    {StreamObjectType::AllocateExtendedGUIDRangeRequest, 0},
    {StreamObjectType::AllocateExtendedGUIDRangeResponse, 0},
    {StreamObjectType::TargetPartitionId, 0},
    {StreamObjectType::PutChangesLockId, 0},
    {StreamObjectType::AdditionalFlags, 0},
    {StreamObjectType::PutChangesResponse, 0},
    {StreamObjectType::RequestHashingOptions, 0},
    {StreamObjectType::DiagnosticRequestOptionOutput, 0},
    {StreamObjectType::DiagnosticRequestOptionInput, 0},
    {StreamObjectType::UserAgentClientAndPlatform, 0},
    {StreamObjectType::VersionTokenKnowledge, 0},
    {StreamObjectType::CellRoundtripOptions, 0},
    {StreamObjectType::FileHash, 0},
};

} // namespace packStore
} // namespace libmson

#endif // STREAMOBJECTTYPES_H
