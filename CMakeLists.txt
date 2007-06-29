project(kdevelop-pg)

# Use colored output (since cmake 2.4.0)
SET(CMAKE_COLOR_MAKEFILE ON)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

add_subdirectory(cmake)
add_subdirectory(include)
ADD_SUBDIRECTORY(kdev-pg)
# cmg doesn't work anymore as KDevelop changed too much
#ADD_SUBDIRECTORY(kdev-cmg)
ADD_SUBDIRECTORY(examples EXCLUDE_FROM_ALL)
