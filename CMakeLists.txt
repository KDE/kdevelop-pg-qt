cmake_minimum_required(VERSION 2.8.9)
project(kdevelop-pg)

enable_testing()

find_package(KDE4)

set(KDEVPGQT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Qt only build
if(NOT KDE4_FOUND)
    # set the cmake policies to the 2.4.x compatibility settings
    cmake_policy(VERSION 2.4.5)
    # CMP0002: multiple targets with the saßme name for the unit tests
    cmake_policy(SET CMP0002 OLD)
    find_package(Qt4)
    set(DATA_INSTALL_DIR share)
    set(LIB_INSTALL_DIR lib)
endif(NOT KDE4_FOUND)

# Use colored output (since cmake 2.4.0)
SET(CMAKE_COLOR_MAKEFILE ON)

# GCC, Clang and MVC supported
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG)
    add_definitions(--std=c++0x)
endif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_CLANG)

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

if(KDE4_FOUND)
    enable_testing()
    add_subdirectory(tests)
endif(KDE4_FOUND)

include(CTest)

# CTestCustom.cmake has to be in the CTEST_BINARY_DIR.
# in the KDE build system, this is the same as CMAKE_BINARY_DIR.
configure_file(${CMAKE_SOURCE_DIR}/CTestCustom.cmake ${CMAKE_BINARY_DIR}/CTestCustom.cmake)
