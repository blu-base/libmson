add_subdirectory(commonTypes)


target_sources(libmson_priv
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/IStreamable.h
    ${CMAKE_CURRENT_LIST_DIR}/PackageStoreFile.h
    ${CMAKE_CURRENT_LIST_DIR}/PackageStoreFileParser.h
    ${CMAKE_CURRENT_LIST_DIR}/RevisionStoreFile.h
    ${CMAKE_CURRENT_LIST_DIR}/RevisionStoreFileParser.h
    ${CMAKE_CURRENT_LIST_DIR}/RevisionStoreFileWriter.h

    ${CMAKE_CURRENT_LIST_DIR}/Revision.h
    ${CMAKE_CURRENT_LIST_DIR}/RevisionManifest.h
    ${CMAKE_CURRENT_LIST_DIR}/RevisionManifestList.h
    ${CMAKE_CURRENT_LIST_DIR}/ObjectSpaceManifestList.h
    ${CMAKE_CURRENT_LIST_DIR}/ObjectGroupList.h

  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/IStreamable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PackageStoreFile.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PackageStoreFileParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/RevisionStoreFile.cpp
    ${CMAKE_CURRENT_LIST_DIR}/RevisionStoreFileParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/RevisionStoreFileWriter.cpp

    ${CMAKE_CURRENT_LIST_DIR}/Revision.cpp
    ${CMAKE_CURRENT_LIST_DIR}/RevisionManifest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/RevisionManifestList.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ObjectSpaceManifestList.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ObjectGroupList.cpp
  )


add_subdirectory(chunkables)
add_subdirectory(utils)
add_subdirectory(propertyTypes)


add_subdirectory(packageTypes)



