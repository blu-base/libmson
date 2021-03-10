add_subdirectory(isf)

########### libmson private library ############

add_library(libmson_priv SHARED)
add_library(libmson::priv ALIAS libmson_priv)
add_subdirectory(priv)

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
    PUBLIC
      Qt5::Core
    PRIVATE
      isf
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

    LIBRARY DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION  "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION  "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)



########## libmson library with public API #####################################
add_library(mson SHARED)

add_subdirectory(interfaces)
add_subdirectory(simpleTypes)

#target_sources(mson
#  PRIVATE
#    ${CMAKE_CURRENT_LIST_DIR}/Notebook.cpp
#    ${CMAKE_CURRENT_LIST_DIR}/Section.cpp
#    ${CMAKE_CURRENT_LIST_DIR}/Page.cpp
#    ${CMAKE_CURRENT_LIST_DIR}/Color.cpp
#    )
target_sources(mson
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Notebook.h
    ${CMAKE_CURRENT_LIST_DIR}/Section.h
    ${CMAKE_CURRENT_LIST_DIR}/Section_p.h
    ${CMAKE_CURRENT_LIST_DIR}/SectionGroup.h
    ${CMAKE_CURRENT_LIST_DIR}/Page.h
    ${CMAKE_CURRENT_LIST_DIR}/Color.h

  )

target_sources(mson
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/FormatIdentifier.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/FormatIdentifier.h
  )


target_link_libraries(
    mson
    PUBLIC
        Qt5::Core

    PRIVATE
#        libmson_priv
    )

  target_include_directories(
      mson PUBLIC
      # Headers used from source/build location:
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
      # Headers used from the installed location:
      "$<INSTALL_INTERFACE:include>"
  )



set_target_properties(mson
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
