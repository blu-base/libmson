#configure_file(Config.h.in ${CMAKE_CURRENT_BINARY_DIR}/Config.h)
set(CMAKE_AUTORCC 1)

#add_subdirectory(common)
#add_subdirectory(import)
#add_subdirectory(export)


############################################################

include_directories(
    )


########### common MSONParser object library ###############
set (MSONParser_common_PART_SRCS
    common/MSONParser_common.cpp
    common/MSONHeader.cpp
    common/FileChunkReference.cpp
    )

add_library(MSONParser_common SHARED ${MSONParser_common_PART_SRCS})

target_link_libraries(
    MSONParser_common
    Qt5::Core
    Qt5::Xml #?
    )

install(TARGETS MSONParser_common DESTINATION ${PLUGIN_INSTALL_DIR}/)

########### import MSONParser library ######################
set (MSONParser_import_PART_SRCS
    import/MSONParser_import.cpp
    import/MSONHeaderReader.cpp
    )
add_library(MSONParser_import SHARED ${MSONParser_import_PART_SRCS})

target_link_libraries(
    MSONParser_import
    Qt5::Core #?
    Qt5::Xml #?
    )

install(TARGETS MSONParser_import DESTINATION ${PLUGIN_INSTALL_DIR}/)

########### export MSONParser library ######################
set (MSONParser_export_PART_SRCS
    export/MSONParser_export.cpp
    )
add_library(MSONParser_export SHARED ${MSONParser_export_PART_SRCS})

target_link_libraries(
    MSONParser_export
    Qt5::Core #?
    Qt5::Xml #?
    )

install(TARGETS MSONParser_export DESTINATION ${PLUGIN_INSTALL_DIR}/)


########### MSONParser libraries wrapper ######################
set (MSONParser_SRCS
    Main.cpp
    )
add_executable(
    MSONParser
    ${MSONParser_SRCS}
    )

target_link_libraries(
    MSONParser
    MSONParser_common
    MSONParser_import
    MSONParser_export
    Qt5::Core #?
    Qt5::Xml #?
    )

install(TARGETS MSONParser DESTINATION ${PLUGIN_INSTALL_DIR}/)
