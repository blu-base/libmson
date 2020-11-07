########### libmson private library ############


// sets LIBMSON_PRIV_CHUNKABLES_PART_SRCS and LIBMSON_PRIV_CHUNKABLES_PART_HEADERS
add_subdirectory(chunkables)


set (LIBMSON_PRIV_PART_SRCS
    ${LIBMSON_PRIV_CHUNKABLES_PART_SRCS}
    RevisionStoreFileWriter.h
    RevisionStoreFileWriter.cpp
    RevisionStoreFileParser.h
    RevisionStoreFileParser.cpp
    RevisionStoreFileManipulator.h
    RevisionStoreFileManipulator.cpp
    )

  set (LIBMSON_PRIV_PART_HEADERS
      ${LIBMSON_PRIV_CHUNKABLES_PART_HEADERS}
    )

add_library(libmson_priv SHARED ${LIBMSON_PRIV_PART_SRCS})

target_link_libraries(
    libmson-priv
    Qt5::Core
    )

  target_include_directories(
      libmson-priv PUBLIC
      # Headers used from source/build location:
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
      # Headers used from the installed location:
      "$<INSTALL_INTERFACE:include>"
  )

install(TARGETS libmson-priv DESTINATION ${PLUGIN_INSTALL_DIR}/)
