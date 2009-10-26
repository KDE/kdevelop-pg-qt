project(kdevelop-pg)

enable_testing()

find_package(KDE4)

if(NOT KDE4_FOUND)
    set(DATA_INSTALL_DIR share)
endif(NOT KDE4_FOUND)

# Use colored output (since cmake 2.4.0)
SET(CMAKE_COLOR_MAKEFILE ON)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include ${QT_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

add_subdirectory(cmake)
add_subdirectory(include)
add_subdirectory(kdev-pg)
add_subdirectory(examples EXCLUDE_FROM_ALL)

add_subdirectory(tests)
