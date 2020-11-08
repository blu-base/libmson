########## Testing executable parse to write ###################################
set (ONE2ONE_SRCS
    Main.cpp
    )
add_executable(
    one2one
    ${ONE2ONE_SRCS}
    )

target_link_libraries(
    one2one
    libmson_priv
    Qt5::Core
    )



install(TARGETS one2one DESTINATION ${CMAKE_INSTALL_BINDIR})
