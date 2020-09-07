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

    common/MSONDocument.cpp

#    common/DocumentSingleton.cpp
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


    common/commonTypes/Enums.cpp
    common/commonTypes/CompactID.cpp
    common/commonTypes/ExtendedGUID.cpp
    common/commonTypes/IFileChunkReference.cpp
    common/commonTypes/FileChunkReference32.cpp
    common/commonTypes/FileChunkReference64.cpp
    common/commonTypes/FileChunkReference64x32.cpp
    common/commonTypes/FileNodeChunkReference.cpp
    common/commonTypes/StringInStorageBuffer.cpp


    common/FileNodeTypes/IFileNodeType.cpp
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

    common/otherTypes/IObjectSpaceOpbjectStream.cpp
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

    common/otherTypes/prtFourBytesOfLengthFollowedByData.cpp



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


    common/helper/Helper.cpp
    )

add_library(MSONcommon SHARED ${MSONcommon_PART_SRCS})

target_link_libraries(
    MSONcommon
    Qt5::Core
    Qt5::Xml #?
    )

install(TARGETS MSONcommon DESTINATION ${PLUGIN_INSTALL_DIR}/)

########### import MSONParser library ######################
set (MSONParser_import_PART_SRCS
    import/MSONParser_import.cpp
    import/MSONHeaderReader.cpp
    import/MSONParser.cpp
    )
add_library(MSONParser_import SHARED ${MSONParser_import_PART_SRCS})

target_link_libraries(
    MSONParser_import
    MSONcommon
    Qt5::Core #?
    Qt5::Xml #?
    )

install(TARGETS MSONParser_import DESTINATION ${PLUGIN_INSTALL_DIR}/)

########### export MSONParser library ######################
set (MSONParser_export_PART_SRCS
    export/MSONParser_export.cpp
    )
add_library(MSONParser_export SHARED ${MSONParser_export_PART_SRCS})

target_link_libraries(
    MSONParser_export
    MSONcommon
    Qt5::Core #?
    Qt5::Xml #?
    )

install(TARGETS MSONParser_export DESTINATION ${PLUGIN_INSTALL_DIR}/)





