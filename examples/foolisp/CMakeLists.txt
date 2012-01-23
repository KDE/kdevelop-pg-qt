project(foolisp_lexer)  

set(parser_STAT_SRCS
    foolisptest.cpp
    )

SET(KDEVPGQT_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/../../kdev-pg/kdev-pg-qt)
SET(KDEVPGQT_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../../../include)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/modules/KDevelop-PG-Qt-config.cmake)
kdevpgqt_generate(parser_SRCS foolisp NAMESPACE FooLisp DEBUG_VISITOR TOKEN_TEXT GENERATE_LEXER
    "${CMAKE_CURRENT_SOURCE_DIR}/foolisp.g"
)

add_executable( foolisptest ${parser_SRCS} ${parser_STAT_SRCS} )
target_link_libraries( foolisptest
    ${QT_QTCORE_LIBRARY}
)
