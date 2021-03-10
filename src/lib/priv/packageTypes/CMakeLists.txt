add_subdirectory(interfaces)

target_sources(libmson_priv
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/CellManifest.h
    ${CMAKE_CURRENT_LIST_DIR}/DataElementFragment.h
    ${CMAKE_CURRENT_LIST_DIR}/DataElement.h
    ${CMAKE_CURRENT_LIST_DIR}/DataElementPackage.h
    ${CMAKE_CURRENT_LIST_DIR}/ObjectDataBLOB.h
    ${CMAKE_CURRENT_LIST_DIR}/ObjectGroup.h
    ${CMAKE_CURRENT_LIST_DIR}/PackagingStructure.h
    ${CMAKE_CURRENT_LIST_DIR}/RevisionManifest.h
    ${CMAKE_CURRENT_LIST_DIR}/StorageIndex.h
    ${CMAKE_CURRENT_LIST_DIR}/StorageManifest.h
    ${CMAKE_CURRENT_LIST_DIR}/StreamObjectHeaderEnd.h
    ${CMAKE_CURRENT_LIST_DIR}/StreamObjectHeader.h
    ${CMAKE_CURRENT_LIST_DIR}/StreamObjectTypes.h
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/CellManifest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DataElement.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DataElementFragment.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DataElementPackage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ObjectDataBLOB.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ObjectGroup.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PackagingStructure.cpp
    ${CMAKE_CURRENT_LIST_DIR}/RevisionManifest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StorageIndex.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StorageManifest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StreamObjectHeader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StreamObjectHeaderEnd.cpp
)

add_subdirectory(streamObjects)

