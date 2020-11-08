########### libmson private library ############

# sets LIBMSON_PRIV_UTILS_PART_SRCS and LIBMSON_PRIV_UTILS_PART_HEADERS
add_subdirectory(utils)

# sets LIBMSON_PRIV_CHUNKABLES_PART_SRCS and LIBMSON_PRIV_CHUNKABLES_PART_HEADERS
add_subdirectory(chunkables)



set (LIBMSON_PRIV_PART_SRCS
    ${LIBMSON_PRIV_CHUNKABLES_PART_SRCS}
    ${LIBMSON_PRIV_UTILS_PART_SRCS}
    RevisionStoreFileWriter.h
    RevisionStoreFileWriter.cpp
    RevisionStoreFileParser.h
    RevisionStoreFileParser.cpp
    RevisionStoreFile.h
    RevisionStoreFile.cpp
    RevisionStoreFileManipulator.h
    RevisionStoreFileManipulator.cpp

    IStreamable.cpp
    )

  set (LIBMSON_PRIV_PART_HEADERS
      IStreamable.h
      ${LIBMSON_PRIV_CHUNKABLES_PART_HEADERS}
      ${LIBMSON_PRIV_UTILS_PART_HEADERS}
    )

add_library(libmson_priv SHARED ${LIBMSON_PRIV_PART_SRCS} ${LIBMSON_PRIV_PART_HEADERS})
add_library(libmson::priv ALIAS libmson_priv)

target_compile_features(libmson_priv PUBLIC cxx_std_17)

# Add definitions for targets
# Values:
#   - Debug  : -DFOO_DEBUG=1
#   - Release: -DFOO_DEBUG=0
#   - others : -DFOO_DEBUG=0
target_compile_definitions(libmson_priv PUBLIC
  "LIBMSON_PRIV_DEBUG=$<CONFIG:Debug>")

target_link_libraries(
    libmson_priv
    Qt5::Core
    )

# Global includes. Used by all targets
# Note:
#   - header can be included by C++ code `#include <foo/foo.h>`
#   - header location in project: ${CMAKE_CURRENT_BINARY_DIR}/generated_headers
target_include_directories(
    libmson_priv PUBLIC
    # Headers used from source/build location:
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    # Headers used from the installed location:
    "$<INSTALL_INTERFACE:include>"
)

# Targets:
#   - <prefix>/lib/libfoo.a
#   - header location after install: <prefix>/foo/foo.h
#   - headers can be included by C++ code `#include <foo/foo.h>`
install(
    TARGETS              libmson_priv
    EXPORT               "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION  "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
