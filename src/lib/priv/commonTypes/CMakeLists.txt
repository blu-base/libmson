target_sources(libmson_priv
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/CompactID.h
    ${CMAKE_CURRENT_LIST_DIR}/Enums.h
    ${CMAKE_CURRENT_LIST_DIR}/ExtendedGUID.h
    ${CMAKE_CURRENT_LIST_DIR}/FileChunkReference32.h
    ${CMAKE_CURRENT_LIST_DIR}/FileChunkReference64.h
    ${CMAKE_CURRENT_LIST_DIR}/FileChunkReference64x32.h
    ${CMAKE_CURRENT_LIST_DIR}/FileNodeChunkReference.h
    ${CMAKE_CURRENT_LIST_DIR}/IFileChunkReference.h
    ${CMAKE_CURRENT_LIST_DIR}/StringInStorageBuffer.h
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/CompactID.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ExtendedGUID.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FileChunkReference32.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FileChunkReference64.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FileChunkReference64x32.cpp
    ${CMAKE_CURRENT_LIST_DIR}/FileNodeChunkReference.cpp
    ${CMAKE_CURRENT_LIST_DIR}/IFileChunkReference.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StringInStorageBuffer.cpp
)
