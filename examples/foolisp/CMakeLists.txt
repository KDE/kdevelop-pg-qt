set(parser_STAT_SRCS
    foolisptest.cpp
    )

set(KDEVPGQT_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/../../kdev-pg/kdev-pg-qt)
set(KDEVPGQT_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../../../include)
include(${CMAKE_CURRENT_BINARY_DIR}/../../KDevelop-PG-QtConfig.cmake)
kdevpgqt_generate(parser_SRCS foolisp NAMESPACE FooLisp DEBUG_VISITOR TOKEN_TEXT GENERATE_LEXER
    "${CMAKE_CURRENT_SOURCE_DIR}/foolisp.g"
)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable( foolisptest ${parser_SRCS} ${parser_STAT_SRCS} )
target_link_libraries( foolisptest Qt6::Core)
