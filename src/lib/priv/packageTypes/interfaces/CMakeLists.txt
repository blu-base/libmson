target_sources(libmson_priv
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/IDataElementBody.h
    ${CMAKE_CURRENT_LIST_DIR}/DataElementType.h
    ${CMAKE_CURRENT_LIST_DIR}/IStreamObject.h
    ${CMAKE_CURRENT_LIST_DIR}/StreamObjectTypes.h
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/IStreamObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StreamObjectTypes.cpp
)

