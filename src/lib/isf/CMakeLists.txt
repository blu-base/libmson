cmake_minimum_required(VERSION 3.5)

project(isf LANGUAGES CXX)

set( ISF_SRCS
    MetricTable.cpp
    MetricBlockEntry.cpp
    MultiByteEncoding.cpp
)

set( ISF_HEADERS
    MetricBlockEntry.h
    MetricEnums.h
    MetricTable.h
    MultiByteEncoding.h
)

add_library(isf STATIC ${ISF_SRCS} ${ISF_HEADERS})

target_link_libraries(isf PUBLIC Qt5::Core)

set(isf_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

set_target_properties(isf
    PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${isf_INCLUDES}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_subdirectory(tests)
