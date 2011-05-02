project(foolisp_lexer)  

set(parser_STAT_SRCS
    foolisptest.cpp
    )

# Add command to generate the parser.
ADD_CUSTOM_COMMAND(
    OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/foolispast.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/foolispparser.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/foolispparser.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/foolispvisitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/foolispvisitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/foolispdefaultvisitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/foolispdefaultvisitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/foolispdebugvisitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/foolisplexer.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/foolisplexer.cpp"
    DEPENDS 
            "${CMAKE_CURRENT_SOURCE_DIR}/foolisp.g"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/../../kdev-pg/kdev-pg-qt
    ARGS    --output=foolisp --namespace=FooLisp --debug-visitor --automata
            "foolisp.g"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

SET(parser_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/foolispparser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/foolispvisitor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/foolispdefaultvisitor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/foolisplexer.cpp")

add_executable( foolisptest ${parser_SRCS} ${parser_STAT_SRCS} )
target_link_libraries( foolisptest
    ${QT_QTCORE_LIBRARY}
)
