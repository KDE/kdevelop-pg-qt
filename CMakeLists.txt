project(kdevelop-pg)

enable_testing()

find_package(KDE4)

# Qt only build
if(NOT KDE4_FOUND)
    cmake_minimum_required(VERSION 2.6.2 FATAL_ERROR)
    # set the cmake policies to the 2.4.x compatibility settings
    cmake_policy(VERSION 2.4.5)
    # CMP0002: multiple targets with the saßme name for the unit tests
    cmake_policy(SET CMP0002 OLD)
    find_package(Qt4)
    set(DATA_INSTALL_DIR share)
endif(NOT KDE4_FOUND)

# Use colored output (since cmake 2.4.0)
SET(CMAKE_COLOR_MAKEFILE ON)

# FIXME: find a way to make this portable (define typeof for non-gcc using decltype etc.)
add_definitions(--std=c++0x)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include ${QT_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

FIND_PROGRAM(FLEX_EXECUTABLE
  NAMES flex
  PATHS /usr/bin
  DOC "Flex executable")

FIND_PROGRAM(BISON_EXECUTABLE
  NAMES bison
  PATHS /usr/bin
  DOC "bison executable")

add_subdirectory(cmake)
add_subdirectory(include)
add_subdirectory(kdev-pg)
add_subdirectory(examples EXCLUDE_FROM_ALL)

if(KDE4_FOUND)
    enable_testing()
    add_subdirectory(tests)
endif(KDE4_FOUND)
