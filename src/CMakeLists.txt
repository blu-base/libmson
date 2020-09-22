#configure_file(Config.h.in ${CMAKE_CURRENT_BINARY_DIR}/Config.h)
set(CMAKE_AUTORCC 1)

#add_subdirectory(common)
#add_subdirectory(import)
#add_subdirectory(export)


############################################################

include_directories(
    )


########### common MSONParser object library ###############
set (MSONcommon_PART_SRCS

    common/MSONHeader.cpp

    common/RevisionStoreFile.cpp

    common/ISerializable.cpp
    common/IDeserializable.cpp
    common/IDebugOutputable.cpp
    common/IRevisionStoreFileToXmlable.cpp



common/DocumentManager.cpp

#    common/MSONStreamReader.cpp
    common/FileNodeListFragment.cpp
    common/FileNodeList.cpp
    common/FileNodeListHeader.cpp
    common/FileNode.cpp
    common/RootFileNodeList.cpp
    common/FreeChunkListFragment.cpp
    common/ObjectGroupList.cpp
    common/ObjectSpaceManifestList.cpp
    common/RevisionManifestList.cpp
    common/RevisionManifest.cpp
    common/TransactionEntry.cpp
    common/TransactionLogFragment.cpp



    common/commonTypes/CompactID.cpp
    common/commonTypes/ExtendedGUID.cpp
    common/commonTypes/IFileChunkReference.cpp
    common/commonTypes/FileChunkReference32.cpp
    common/commonTypes/FileChunkReference64.cpp
    common/commonTypes/FileChunkReference64x32.cpp
    common/commonTypes/FileNodeChunkReference.cpp
    common/commonTypes/StringInStorageBuffer.cpp



    common/FileNodeTypes/ObjectSpaceManifestRootFND.cpp
    common/FileNodeTypes/ObjectSpaceManifestListReferenceFND.cpp
    common/FileNodeTypes/ObjectSpaceManifestListStartFND.cpp
    common/FileNodeTypes/RevisionManifestListReferenceFND.cpp
    common/FileNodeTypes/RevisionManifestListStartFND.cpp
    common/FileNodeTypes/RevisionManifestStart4FND.cpp
    common/FileNodeTypes/RevisionManifestStart6FND.cpp
    common/FileNodeTypes/RevisionManifestStart7FND.cpp
    common/FileNodeTypes/GlobalIdTableStartFNDX.cpp
    common/FileNodeTypes/GlobalIdTableEntryFNDX.cpp
    common/FileNodeTypes/GlobalIdTableEntry2FNDX.cpp
    common/FileNodeTypes/GlobalIdTableEntry3FNDX.cpp
    common/FileNodeTypes/ObjectRevisionWithRefCountFNDX.cpp
    common/FileNodeTypes/ObjectRevisionWithRefCount2FNDX.cpp
    common/FileNodeTypes/RootObjectReference2FNDX.cpp
    common/FileNodeTypes/RootObjectReference3FND.cpp
    common/FileNodeTypes/RevisionRoleDeclarationFND.cpp
    common/FileNodeTypes/RevisionRoleAndContextDeclarationFND.cpp
    common/FileNodeTypes/ObjectDataEncryptionKeyV2FNDX.cpp
    common/FileNodeTypes/ObjectInfoDependencyOverridesFND.cpp
    common/FileNodeTypes/FileDataStoreListReferenceFND.cpp
    common/FileNodeTypes/FileDataStoreObjectReferenceFND.cpp
    common/FileNodeTypes/ObjectDeclarationWithRefCountFNDX.cpp
    common/FileNodeTypes/ObjectDeclarationWithRefCountFNDX.cpp
    common/FileNodeTypes/ObjectDeclarationWithRefCount2FNDX.cpp
    common/FileNodeTypes/ObjectDeclaration2RefCountFND.cpp
    common/FileNodeTypes/ObjectDeclaration2LargeRefCountFND.cpp
    common/FileNodeTypes/ObjectDeclarationFileData3RefCountFND.cpp
    common/FileNodeTypes/ObjectDeclarationFileData3LargeRefCountFND.cpp
    common/FileNodeTypes/ReadOnlyObjectDeclaration2RefCountFND.cpp
    common/FileNodeTypes/ReadOnlyObjectDeclaration2LargeRefCountFND.cpp
    common/FileNodeTypes/ObjectGroupListReferenceFND.cpp
    common/FileNodeTypes/ObjectGroupStartFND.cpp
    common/FileNodeTypes/DataSignatureGroupDefinitionFND.cpp
    common/FileNodeTypes/HashedChunkDescriptor2FND.cpp
    common/FileNodeTypes/ObjectGroupEndFND.cpp
    common/FileNodeTypes/GlobalIdTableEndFNDX.cpp
    common/FileNodeTypes/GlobalIdTableStart2FND.cpp
    common/FileNodeTypes/RevisionManifestEndFND.cpp
    common/FileNodeTypes/ChunkTerminatorFND.cpp


    common/otherTypes/ObjectSpaceObjectPropSet.cpp

    common/otherTypes/IObjectSpaceObjectStream.cpp
    common/otherTypes/ObjectSpaceObjectStreamOfOIDs.cpp
    common/otherTypes/ObjectSpaceObjectStreamOfOSIDs.cpp
    common/otherTypes/ObjectSpaceObjectStreamOfContextIDs.cpp

    common/otherTypes/ObjectSpaceObjectStreamHeader.cpp


    common/otherTypes/ObjectInfoDependencyOverride32.cpp
    common/otherTypes/ObjectInfoDependencyOverride8.cpp
    common/otherTypes/ObjectInfoDependencyOverrideData.cpp
    common/otherTypes/ObjectDeclarationWithRefCountBody.cpp
    common/otherTypes/ObjectDeclaration2Body.cpp
    common/otherTypes/FileDataStoreObject.cpp

    common/properties/JCID.cpp


    common/properties/IProperty.cpp
    common/properties/PropertyID.cpp
    common/properties/PropertySet.cpp

    common/properties/IPropertyType.cpp
    common/properties/PropertyType_NoData.cpp
    common/properties/PropertyType_Bool.cpp
    common/properties/PropertyType_OneByteOfData.cpp
    common/properties/PropertyType_TwoBytesOfData.cpp
    common/properties/PropertyType_FourBytesOfData.cpp
    common/properties/PropertyType_EightBytesOfData.cpp
    common/properties/PropertyType_ArrayNumber.cpp
    common/properties/PropertyType_ArrayOfPropertyValues.cpp
    common/properties/PropertyType_ContextID.cpp
    common/properties/PropertyType_FourBytesOfLengthFollowedByData.cpp
    common/properties/PropertyType_ObjectID.cpp
    common/properties/PropertyType_ObjectSpaceID.cpp
    common/properties/PropertyType_PropertySet.cpp


    common/simpleTypes/LayoutAlignment.cpp
    common/simpleTypes/BodyTextAlignment.cpp
    common/simpleTypes/Time32.cpp
    common/simpleTypes/FileTime.cpp
    common/simpleTypes/LCID.cpp
    common/simpleTypes/ColorRef.cpp
    common/simpleTypes/ListMSAAIndex.cpp
    common/simpleTypes/PageSize.cpp
    common/simpleTypes/NoteTagShape.cpp


    common/helper/Helper.cpp
    )

  set (MSONcommon_PART_HEADERS
    common/commonTypes/Enums.h
    common/IRevisionStoreFileObject.h
    common/FileNodeTypes/IFileNodeType.h
    common/properties/IPropertyType.h
    common/properties/IProperty.h
    )

add_library(MSONcommon SHARED ${MSONcommon_PART_SRCS})

target_link_libraries(
    MSONcommon
    Qt5::Core
    Qt5::Xml #?
    )

  target_include_directories(
      MSONcommon PUBLIC
      # Headers used from source/build location:
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
      # Headers used from the installed location:
      "$<INSTALL_INTERFACE:include>"
  )

install(TARGETS MSONcommon DESTINATION ${PLUGIN_INSTALL_DIR}/)
