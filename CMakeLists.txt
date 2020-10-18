cmake_minimum_required(VERSION 3.5)


project(MSONParser LANGUAGES CXX)

message(STATUS "Using CMake version: ${CMAKE_VERSION}")
include(FeatureSummary)

# ### Constant definitions ###

set(QT_MIN_VERSION     "5.10.0")
set(KF5_MIN_VERSION    "5.56.0")

# use CPP-11
if (CMAKE_VERSION VERSION_LESS "3.1")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else ()
    set (CMAKE_CXX_STANDARD 17)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)



find_package(
    Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED
        Core
        Xml
        Test
)


add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(resources)
add_subdirectory(docs)



########### MSONParser libraries wrapper ######################
set (MSONParser_SRCS
    src/Main.cpp
    )
add_executable(
    one2xml
    ${MSONParser_SRCS}
    )

target_link_libraries(
    one2xml
    MSONcommon
    Qt5::Core #?
    Qt5::Xml #?
    )



install(TARGETS one2xml DESTINATION ${PLUGIN_INSTALL_DIR}/)


########### MSONParser test  ######################
set (ONE2ONE_SRCS
    src/Test.cpp
    )
add_executable(
    one2one
    ${ONE2ONE_SRCS}
    )

target_link_libraries(
    one2one
    MSONcommon
    libmson
    Qt5::Core
    )



install(TARGETS one2one DESTINATION ${PLUGIN_INSTALL_DIR}/)



feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
