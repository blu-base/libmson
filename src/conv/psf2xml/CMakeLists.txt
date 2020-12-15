########### psf2xml ############################################################

set (PSF2XML_SRCS
    PSFtoXml.cpp
    Main.cpp
    )

add_executable(
    psf2xml
    ${PSF2XML_SRCS}
    )

target_link_libraries(
    psf2xml
    libmson_priv
    libmson
    Qt5::Core
    Qt5::Xml
    )

install(TARGETS psf2xml DESTINATION ${CMAKE_INSTALL_BINDIR})
