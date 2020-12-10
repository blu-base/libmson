#ifndef RSFTOXML_H
#define RSFTOXML_H

#include <QtCore/qglobal.h>

#include <QFile>
#include <QXmlStreamWriter>

/// \todo make a proper library import....
#include "../../lib/priv/RevisionStoreFile.h"
#include "../../lib/priv/chunkables/Chunkable.h"


#include "../../lib/priv/chunkables/ObjectSpaceObjectPropSet.h"

#include "../../lib/priv/chunkables/fileNodeTypes/FileNodeTypes.h"


#include "../../lib/priv/commonTypes/StringInStorageBuffer.h"

#include "../../lib/priv/propertyTypes/PropertyID.h"
#include "../../lib/priv/propertyTypes/PropertySet.h"
#include "../../lib/priv/propertyTypes/PropertyType_ArrayNumber.h"
#include "../../lib/priv/propertyTypes/PropertyType_ArrayOfPropertyValues.h"
#include "../../lib/priv/propertyTypes/PropertyType_Bool.h"
#include "../../lib/priv/propertyTypes/PropertyType_ContextID.h"
#include "../../lib/priv/propertyTypes/PropertyType_EightBytesOfData.h"
#include "../../lib/priv/propertyTypes/PropertyType_FourBytesOfData.h"
#include "../../lib/priv/propertyTypes/PropertyType_FourBytesOfLengthFollowedByData.h"
#include "../../lib/priv/propertyTypes/PropertyType_NoData.h"
#include "../../lib/priv/propertyTypes/PropertyType_ObjectID.h"
#include "../../lib/priv/propertyTypes/PropertyType_ObjectSpaceID.h"
#include "../../lib/priv/propertyTypes/PropertyType_OneByteOfData.h"
#include "../../lib/priv/propertyTypes/PropertyType_PropertySet.h"
#include "../../lib/priv/propertyTypes/PropertyType_TwoBytesOfData.h"


#include "../../lib/publ/simpleTypes/BodyTextAlignment.h"
#include "../../lib/publ/simpleTypes/Charset.h"
#include "../../lib/publ/simpleTypes/ColorRef.h"
#include "../../lib/publ/simpleTypes/FileTime.h"
#include "../../lib/publ/simpleTypes/LCID.h"
#include "../../lib/publ/simpleTypes/LayoutAlignment.h"
#include "../../lib/publ/simpleTypes/ListMSAAIndex.h"
#include "../../lib/publ/simpleTypes/NoteTagShape.h"
#include "../../lib/publ/simpleTypes/PageSize.h"
#include "../../lib/publ/simpleTypes/Time32.h"

#include "../../lib/priv/chunkables/objectTypes/IObjectSpaceObjectStream.h"
#include "../../lib/priv/chunkables/objectTypes/ObjectDeclaration2Body.h"
#include "../../lib/priv/chunkables/objectTypes/ObjectDeclarationWithRefCountBody.h"
#include "../../lib/priv/chunkables/objectTypes/ObjectInfoDependencyOverride32.h"
#include "../../lib/priv/chunkables/objectTypes/ObjectInfoDependencyOverride8.h"
#include "../../lib/priv/chunkables/objectTypes/ObjectSpaceObjectStreamHeader.h"
#include "../../lib/priv/chunkables/objectTypes/ObjectSpaceObjectStreamOfContextIDs.h"
#include "../../lib/priv/chunkables/objectTypes/ObjectSpaceObjectStreamOfOIDs.h"
#include "../../lib/priv/chunkables/objectTypes/ObjectSpaceObjectStreamOfOSIDs.h"


using namespace libmson::priv;

class RSFtoXml {

public:
  static bool writeRSFTree(
      QFile& outputFile,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile);
  static bool writeRSFSequence(
      QFile& outputFile,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile);

private:
  // ---------------------------------------------------------------------------
  // chunkable Types
  // ---------------------------------------------------------------------------
  static QXmlStreamWriter& writeChunkable(
      const Chunkable_SPtr_t& chunk, const bool followRecursively,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);

  // ---------------------------------------------------------------------------

  static QXmlStreamWriter& writeRevisionStoreFileHeader(
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      const bool followRecursively, QXmlStreamWriter& xmlWriter);

  static QXmlStreamWriter& writeEncryptedData(
      const std::shared_ptr<EncryptedData>& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeFileDataStoreObject(
      const std::shared_ptr<FileDataStoreObject>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeFileNode(
      const std::shared_ptr<FileNode>& obj, const bool followRecursively,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeFileNodeListFragment(
      const std::shared_ptr<FileNodeListFragment>& obj,
      const bool followRecursively,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeFreeChunk(QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeFreeChunkListFragment(
      const std::shared_ptr<FreeChunkListFragment>& obj,
      const bool followRecursively,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectInfoDependencyOverrideData(
      const std::shared_ptr<ObjectInfoDependencyOverrideData>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectInfoDependencyOverrideData(
      const ObjectInfoDependencyOverrideData& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectSpaceObjectPropSet(
      const std::shared_ptr<ObjectSpaceObjectPropSet>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeTransactionLogFragment(
      const std::shared_ptr<TransactionLogFragment>& obj,
      const bool followRecursively,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeUnknownBlob(
      const std::shared_ptr<UnknownBlob>& obj, QXmlStreamWriter& xmlWriter);


  // ---------------------------------------------------------------------------
  // file node data types
  // ---------------------------------------------------------------------------
  static QXmlStreamWriter& writeIFileNodeType(
      const IFileNodeType_SPtr_t& obj, const bool followRecursively,
      const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);

  // ---------------------------------------------------------------------------
  static QXmlStreamWriter& writeChunkTerminatorFND(QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeDataSignatureGroupDefinitionFND(
      const DataSignatureGroupDefinitionFND_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeFileDataStoreListReferenceFND(
      const FileDataStoreListReferenceFND_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeFileDataStoreObjectReferenceFND(
      const FileDataStoreObjectReferenceFND_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeGlobalIdTableEndFNDX(QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeGlobalIdTableEntry2FNDX(
      const GlobalIdTableEntry2FNDX_SPtr_t& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeGlobalIdTableEntry3FNDX(
      const GlobalIdTableEntry3FNDX_SPtr_t& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeGlobalIdTableEntryFNDX(
      const GlobalIdTableEntryFNDX_SPtr_t& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeGlobalIdTableStart2FND(QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeGlobalIdTableStartFNDX(
      const GlobalIdTableStartFNDX_SPtr_t& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeHashedChunkDescriptor2FND(
      const HashedChunkDescriptor2FND_SPtr_t& obj, const bool followRecursively,
      const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectDataEncryptionKeyV2FNDX(
      const ObjectDataEncryptionKeyV2FNDX_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectDeclaration2LargeRefCountFND(
      const ObjectDeclaration2LargeRefCountFND_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectDeclaration2RefCountFND(
      const ObjectDeclaration2RefCountFND_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectDeclarationFileData3LargeRefCountFND(
      const ObjectDeclarationFileData3LargeRefCountFND_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectDeclarationFileData3RefCountFND(
      const ObjectDeclarationFileData3RefCountFND_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectDeclarationWithRefCount2FNDX(
      const ObjectDeclarationWithRefCount2FNDX_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectDeclarationWithRefCountFNDX(
      const ObjectDeclarationWithRefCountFNDX_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectGroupEndFND(QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectGroupListReferenceFND(
      const ObjectGroupListReferenceFND_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectGroupStartFND(
      const ObjectGroupStartFND_SPtr_t& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectInfoDependencyOverridesFND(
      const ObjectInfoDependencyOverridesFND_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectRevisionWithRefCount2FNDX(
      const ObjectRevisionWithRefCount2FNDX_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectRevisionWithRefCountFNDX(
      const ObjectRevisionWithRefCountFNDX_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectSpaceManifestListReferenceFND(
      const ObjectSpaceManifestListReferenceFND_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectSpaceManifestListStartFND(
      const ObjectSpaceManifestListStartFND_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectSpaceManifestRootFND(
      const ObjectSpaceManifestRootFND_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeReadOnlyObjectDeclaration2LargeRefCountFND(
      const ReadOnlyObjectDeclaration2LargeRefCountFND_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeReadOnlyObjectDeclaration2RefCountFND(
      const ReadOnlyObjectDeclaration2RefCountFND_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeRevisionManifestEndFND(QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRevisionManifestListReferenceFND(
      const RevisionManifestListReferenceFND_SPtr_t& obj,
      const bool followRecursively, const FileNode_SPtr_t& parent,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRevisionManifestListStartFND(
      const RevisionManifestListStartFND_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRevisionManifestStart4FND(
      const RevisionManifestStart4FND_SPtr_t& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRevisionManifestStart6FND(
      const RevisionManifestStart6FND_SPtr_t& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRevisionManifestStart7FND(
      const RevisionManifestStart7FND_SPtr_t& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRevisionRoleAndContextDeclarationFND(
      const RevisionRoleAndContextDeclarationFND_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRevisionRoleDeclarationFND(
      const RevisionRoleDeclarationFND_SPtr_t& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRootObjectReference2FNDX(
      const RootObjectReference2FNDX_SPtr_t& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeRootObjectReference3FND(
      const RootObjectReference3FND_SPtr_t& obj, QXmlStreamWriter& xmlWriter);

  // ---------------------------------------------------------------------------
  // object Types
  // ---------------------------------------------------------------------------
  static QXmlStreamWriter& writeIObjectSpaceObjectStream(
      const IObjectSpaceObjectStream& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectDeclaration2Body(
      const ObjectDeclaration2Body& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectDeclarationWithRefCountBody(
      const ObjectDeclarationWithRefCountBody& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectInfoDependencyOverride32(
      const ObjectInfoDependencyOverride32& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectInfoDependencyOverride8(
      const ObjectInfoDependencyOverride8& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectSpaceObjectStreamHeader(
      const ObjectSpaceObjectStreamHeader& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectSpaceObjectStreamOfContextIDs(
      const ObjectSpaceObjectStreamOfContextIDs& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectSpaceObjectStreamOfOIDs(
      const ObjectSpaceObjectStreamOfOIDs& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeObjectSpaceObjectStreamOfOSIDs(
      const ObjectSpaceObjectStreamOfOSIDs& obj, QXmlStreamWriter& xmlWriter);

  // ---------------------------------------------------------------------------
  // common Types
  // ---------------------------------------------------------------------------
  static QXmlStreamWriter&
  writeCompactID(const CompactID& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeExtendedGUID(const ExtendedGUID& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeGUID(const QUuid& obj, QXmlStreamWriter& xmlWriter);
  //  static QXmlStreamWriter& writeFileChunkReference32(
  //      const FileChunkReference32& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeFileChunkReference64(
      const FileChunkReference64& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeFileChunkReference64x32(
      const FileChunkReference64x32& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeFileNodeChunkReference(
      const FileNodeChunkReference& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeStringInStorageBuffer(
      const StringInStorageBuffer& obj, QXmlStreamWriter& xmlWriter);

  // ---------------------------------------------------------------------------
  // property Types
  // ---------------------------------------------------------------------------
  static QXmlStreamWriter&
  writeJCID(const JCID& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writePropertyID(const PropertyID& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeIPropertyType(
      const std::shared_ptr<IPropertyType>& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writePropertySet(const PropertySet& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_ArrayNumber(
      const std::shared_ptr<PropertyType_ArrayNumber>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_ArrayOfPropertyValues(
      const std::shared_ptr<PropertyType_ArrayOfPropertyValues>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_Bool(QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_ContextID(
      const std::shared_ptr<PropertyType_ContextID>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_EightBytesOfData(
      const std::shared_ptr<PropertyType_EightBytesOfData>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_FourBytesOfData(
      const std::shared_ptr<PropertyType_FourBytesOfData>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_FourBytesOfLengthFollowedByData(
      const std::shared_ptr<PropertyType_FourBytesOfLengthFollowedByData>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writePropertyType_NoData(QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_ObjectID(
      const std::shared_ptr<PropertyType_ObjectID>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writePropertyType_ObjectSpaceID(QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_OneByteOfData(
      const std::shared_ptr<PropertyType_OneByteOfData>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_PropertySet(
      const std::shared_ptr<PropertyType_PropertySet>& obj,
      QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writePropertyType_TwoBytesOfData(
      const std::shared_ptr<PropertyType_TwoBytesOfData>& obj,
      QXmlStreamWriter& xmlWriter);


  // MS-ONE stuff

  // ---------------------------------------------------------------------------
  // simpleTypes
  // ---------------------------------------------------------------------------
  static QXmlStreamWriter& writeBodyTextAlignment(
      const libmson::BodyTextAlignment& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeFileTime(const libmson::FileTime& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeLayoutAlignment(
      const libmson::LayoutAlignment& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeLCID(const libmson::LCID& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeListMSAAIndex(
      const libmson::ListMSAAIndex& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter& writeNoteTagShape(
      const libmson::NoteTagShape& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writePageSize(const libmson::PageSize& obj, QXmlStreamWriter& xmlWriter);
  static QXmlStreamWriter&
  writeTime32(const libmson::Time32& obj, QXmlStreamWriter& xmlWriter);

  // ---------------------------------------------------------------------------
  // complex types
  // ---------------------------------------------------------------------------
  static QXmlStreamWriter&
  writeColorRef(const libmson::ColorRef& obj, QXmlStreamWriter& xmlWriter);


  // ---------------------------------------------------------------------------
  // utils
  // ---------------------------------------------------------------------------

  //  /**
  //   * Will print FileChunkReference32 to xmlWriter if followRercursively ==
  //   * false. If followRecursively is true, the Chunkable will be inserted
  //   * instead, to walk the references tree.
  //   *
  //   */
  //  static QXmlStreamWriter& getFcr32orChunk(
  //      const Chunkable_SPtr_t& chunk, bool followRecursively,
  //      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
  //      QXmlStreamWriter& xmlWriter);

  /**
   * Will print FileChunkReference64 to xmlWriter if followRercursively ==
   * false. If followRecursively is true, the Chunkable will be inserted
   * instead, to walk the references tree.
   *
   */
  static QXmlStreamWriter& writeFcr64orChunk(
      const Chunkable_SPtr_t& chunk, bool followRecursively, FCR_INIT init,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);

  /**
   * Will print FileChunkReference64x32 to xmlWriter if followRercursively ==
   * false. If followRecursively is true, the Chunkable will be inserted
   * instead, to walk the references tree.
   *
   */
  static QXmlStreamWriter& writeFcr64x32orChunk(
      const Chunkable_SPtr_t& chunk, bool followRecursively, FCR_INIT init,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);

  /**
   * Will print FileNodeChunkReference to xmlWriter if followRercursively ==
   * false. If followRecursively is true, the Chunkable will be inserted
   * instead, to walk the references tree.
   *
   */
  static QXmlStreamWriter& writeFncrOrChunk(
      const Chunkable_SPtr_t& chunk, bool followRecursively,
      FNCR_STP_FORMAT stpFormat, FNCR_CB_FORMAT cbFormat, FCR_INIT init,
      const std::shared_ptr<RevisionStoreFile>& revisionStoreFile,
      QXmlStreamWriter& xmlWriter);
};


#endif // RSFTOXML_H
