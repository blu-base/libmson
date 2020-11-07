
########## libmson library with public API #####################################
set (libmson_PART_SRCS
)

set (libmson_PART_HEADERS
)

add_library(libmson SHARED ${libmson_PART_SRCS})

target_link_libraries(
    libmson
    Qt5::Core
    )

  target_include_directories(
      libmson PUBLIC
      # Headers used from source/build location:
      "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
      # Headers used from the installed location:
      "$<INSTALL_INTERFACE:include>"
  )

install(TARGETS libmson DESTINATION ${PLUGIN_INSTALL_DIR}/)
