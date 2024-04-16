set(parser_STAT_SRCS
  phptest.cpp
)

set(KDEVPGQT_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/../../kdev-pg/kdev-pg-qt)

kdevpgqt_generate(parser_SRCS php NAMESPACE Php DEBUG_VISITOR TOKEN_TEXT GENERATE_LEXER
    "${CMAKE_CURRENT_SOURCE_DIR}/php.g"
)

add_definitions(-fexceptions)

add_executable( phptest ${parser_SRCS} ${parser_STAT_SRCS} )
target_link_libraries( phptest Qt6::Core)
