########### rsf2xml ############################################################

set (RSF2XML_SRCS
    RSFtoXml.cpp
    Main.cpp
    )

add_executable(
    rsf2xml
    ${RSF2XML_SRCS}
    )

target_link_libraries(
    rsf2xml
    libmson_priv
    mson
    Qt5::Core
    Qt5::Xml
    isf
    )

install(TARGETS rsf2xml DESTINATION ${CMAKE_INSTALL_BINDIR})
