#ifndef STREAMOBJECTTYPES_H
#define STREAMOBJECTTYPES_H

#include <QString>
#include <cstdint>
#include <map>
#include <set>

namespace libmson {
namespace fsshttpb {

enum class StreamObjectType : uint16_t {
  Invalid = 0,
  /* 16 bit header typers */
  DataElement                          = 0x01,
  ObjectDataBLOB                       = 0x02,
  ObjectGroupObjectExcludedData        = 0x03,
  WaterlineKnowledgeEntry              = 0x04,
  ObjectGroupObjectDataBLOBDeclaration = 0x05,
  DataElementHash                      = 0x06,
  StorageManifestRootDeclare           = 0x07,
  RevisionManifestRootDeclare          = 0x00A,
  CellManifestCurrentRevision          = 0x00B,
  StorageManifestSchemaGUID            = 0x00C,
  StorageIndexRevisionMapping          = 0x00D,
  StorageIndexCellMapping              = 0x00E,
  CellKnowledgeRange                   = 0x00F,
  Knowledge                            = 0x010,
  StorageIndexManifestMapping          = 0x011,
  CellKnowledge                        = 0x014,
  DataElementPackage                   = 0x015,
  ObjectGroupObjectData                = 0x016,
  CellKnowledgeEntry                   = 0x017,
  ObjectGroupObjectDeclare             = 0x018,
  RevisionManifestObjectGroupReference = 0x019,
  RevisionManifest                     = 0x01A,
  ObjectGroupObjectDataBLOBReference   = 0x01C,
  ObjectGroupDeclarations              = 0x01D,
  ObjectGroupData                      = 0x01E,
  WaterlineKnowledge                   = 0x029,
  ContentTagKnowledge                  = 0x02D,
  ContentTagKnowledgeEntry             = 0x02E,
  QueryChangesVersioning               = 0x030,
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

/** If compound type is true, then a StreamObjectHeaderEnd must follow */
const std::map<StreamObjectType, bool> compoundType = {
    {StreamObjectType::Invalid, false},
    /* 16bit header typers */
    {StreamObjectType::DataElement, true},
    {StreamObjectType::ObjectDataBLOB, false},
    {StreamObjectType::ObjectGroupObjectExcludedData, false},
    {StreamObjectType::WaterlineKnowledgeEntry, false},
    {StreamObjectType::ObjectGroupObjectDataBLOBDeclaration, false},
    {StreamObjectType::DataElementHash, false},
    {StreamObjectType::StorageManifestRootDeclare, false},
    {StreamObjectType::RevisionManifestRootDeclare, false},
    {StreamObjectType::CellManifestCurrentRevision, false},
    {StreamObjectType::StorageManifestSchemaGUID, false},
    {StreamObjectType::StorageIndexRevisionMapping, false},
    {StreamObjectType::StorageIndexCellMapping, false},
    {StreamObjectType::CellKnowledgeRange, false},
    {StreamObjectType::Knowledge, true},
    {StreamObjectType::StorageIndexManifestMapping, false},
    {StreamObjectType::CellKnowledge, true},
    {StreamObjectType::DataElementPackage, true},
    {StreamObjectType::ObjectGroupObjectData, false},
    {StreamObjectType::CellKnowledgeEntry, false},
    {StreamObjectType::ObjectGroupObjectDeclare, false},
    {StreamObjectType::RevisionManifestObjectGroupReference, false},
    {StreamObjectType::RevisionManifest, false},
    {StreamObjectType::ObjectGroupObjectDataBLOBReference, false},
    {StreamObjectType::ObjectGroupDeclarations, true},
    {StreamObjectType::ObjectGroupData, true},
    {StreamObjectType::WaterlineKnowledge, true},
    {StreamObjectType::ContentTagKnowledge, true},
    {StreamObjectType::ContentTagKnowledgeEntry, false},
    {StreamObjectType::QueryChangesVersioning, false},
    /* 32bit header types */
    {StreamObjectType::Request, true},
    {StreamObjectType::Subresponse, true},
    {StreamObjectType::Subrequest, true},
    {StreamObjectType::ReadAccessResponse, true},
    {StreamObjectType::SpecializedKnowledge, true},
    {StreamObjectType::WriteAccessResponse, true},
    {StreamObjectType::QueryChangesFilter, true},
    {StreamObjectType::ErrorWin32, false},
    {StreamObjectType::ErrorProtocol, false},
    {StreamObjectType::Error, true},
    {StreamObjectType::ErrorStringSupplementalInfo, false},
    {StreamObjectType::UserAgentVersion, false},
    {StreamObjectType::QueryChangesFilterSchemaSpecific, false},
    {StreamObjectType::QueryChangesRequest, false},
    {StreamObjectType::ErrorHRESULT, false},
    {StreamObjectType::QueryChangesFilterDataElementIDs, false},
    {StreamObjectType::UserAgentGUID, false},
    {StreamObjectType::QueryChangesFilterDataElementType, false},
    {StreamObjectType::QueryChangesDataConstraint, false},
    {StreamObjectType::PutChangesRequest, false},
    {StreamObjectType::QueryChangesRequestArguments, false},
    {StreamObjectType::QueryChangesFilterCellID, false},
    {StreamObjectType::UserAgent, true},
    {StreamObjectType::QueryChangesResponse, false},
    {StreamObjectType::QueryChangesFilterHierarchy, false},
    {StreamObjectType::Response, true},
    {StreamObjectType::ErrorCell, false},
    {StreamObjectType::QueryChangesFilterFlags, false},
    {StreamObjectType::DataElementFragment, false},
    {StreamObjectType::FragmentKnowledge, true},
    {StreamObjectType::FragmentKnowledgeEntry, false},
    {StreamObjectType::ObjectGroupMetadata, false},
    {StreamObjectType::ObjectGroupMetadataDeclarations, true},
    {StreamObjectType::ONPackageStart, true},
    {StreamObjectType::AllocateExtendedGUIDRangeRequest, false},
    {StreamObjectType::AllocateExtendedGUIDRangeResponse, false},
    {StreamObjectType::TargetPartitionId, false},
    {StreamObjectType::PutChangesLockId, false},
    {StreamObjectType::AdditionalFlags, false},
    {StreamObjectType::PutChangesResponse, false},
    {StreamObjectType::RequestHashingOptions, false},
    {StreamObjectType::DiagnosticRequestOptionOutput, false},
    {StreamObjectType::DiagnosticRequestOptionInput, false},
    {StreamObjectType::UserAgentClientAndPlatform, false},
    {StreamObjectType::VersionTokenKnowledge, false},
    {StreamObjectType::CellRoundtripOptions, false},
    {StreamObjectType::FileHash, false},
};

QString streamObjectTypeToString(const StreamObjectType& type);

} // namespace packStore
} // namespace libmson

#endif // STREAMOBJECTTYPES_H
