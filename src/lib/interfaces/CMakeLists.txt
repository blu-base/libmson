target_sources(mson
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/INode.h
    ${CMAKE_CURRENT_LIST_DIR}/ICascadedTextAttributed.h
    ${CMAKE_CURRENT_LIST_DIR}/IFileObjectAttributed.h
    ${CMAKE_CURRENT_LIST_DIR}/IActionItemAttributed.h
    ${CMAKE_CURRENT_LIST_DIR}/IHierarchyObjectAttributed.h
    ${CMAKE_CURRENT_LIST_DIR}/IEditedByAttributed.h
    ${CMAKE_CURRENT_LIST_DIR}/ISection.h
    ${CMAKE_CURRENT_LIST_DIR}/IStreamable.h
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/IStreamable.cpp
  )
