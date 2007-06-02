project(kdevelop-pg)
#if you don't want the full compiler output, remove the following line
#SET(CMAKE_VERBOSE_MAKEFILE ON)

# Use colored output (since cmake 2.4.0)
SET(CMAKE_COLOR_MAKEFILE ON)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

ADD_SUBDIRECTORY(kdev-pg)
ADD_SUBDIRECTORY(kdev-cmg)
ADD_SUBDIRECTORY(examples EXCLUDE_FROM_ALL)
