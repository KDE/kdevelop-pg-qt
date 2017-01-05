INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

find_package(KDevelop-PG-Qt)

kdevpgqt_generate(_kdevpgList fact NAMESPACE fact DEBUG_VISITOR
    "${CMAKE_CURRENT_SOURCE_DIR}/fact.g"
    "${CMAKE_CURRENT_SOURCE_DIR}/factlexer.h"
)

set( parser_SRCS
    ${_kdevpgList}
)

SET(assembled_parser_srcs
    factlexer.cpp
)


# add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -O2)

# tell CMake to generate the executable
ADD_EXECUTABLE(fact-parser ${assembled_parser_srcs} ${parser_SRCS} main.cpp)

target_link_libraries(fact-parser Qt5::Core)

