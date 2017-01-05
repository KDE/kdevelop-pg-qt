set(parser_STAT_SRCS
  phptest.cpp
)

SET(KDEVPGQT_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/../../kdev-pg/kdev-pg-qt)
include(${CMAKE_CURRENT_BINARY_DIR}/../../KDevelop-PG-QtConfig.cmake)

kdevpgqt_generate(parser_SRCS php NAMESPACE Php DEBUG_VISITOR TOKEN_TEXT GENERATE_LEXER
    "${CMAKE_CURRENT_SOURCE_DIR}/php.g"
)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_definitions(-fexceptions)

add_executable( phptest ${parser_SRCS} ${parser_STAT_SRCS} )
target_link_libraries( phptest Qt5::Core)

