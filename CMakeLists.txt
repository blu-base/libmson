cmake_minimum_required(VERSION 3.5)

project(libmson LANGUAGES CXX)

message(STATUS "Using CMake version: ${CMAKE_VERSION}")
include(FeatureSummary)

########## Constant definitions ################################################
set(QT_MIN_VERSION     "5.10.0")
set(KF5_MIN_VERSION    "5.56.0")

########## Use CPP-17 ##########################################################
if (CMAKE_VERSION VERSION_LESS "3.1")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else ()
    set (CMAKE_CXX_STANDARD 17)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)




########## Find Qt #############################################################
find_package(
    Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED
        Core
        Xml
        Test
)

set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_AUTORCC ON)




add_subdirectory(src)

add_subdirectory(tests)
add_subdirectory(resources)
add_subdirectory(docs)




feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES 
    FATAL_ON_MISSING_REQUIRED_PACKAGES)
