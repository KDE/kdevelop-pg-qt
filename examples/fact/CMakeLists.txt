
PROJECT(fact_parser)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Add command to generate the parser.
ADD_CUSTOM_COMMAND(
    OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/factast.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/factparser.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/factparser.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/factvisitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/factvisitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/factdefaultvisitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/factdefaultvisitor.cpp"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/fact.g"
            "${CMAKE_CURRENT_SOURCE_DIR}/factlexer.h"
    COMMAND ${CMAKE_BINARY_DIR}/kdev-pg/kdev-pg-qt
    ARGS    --output=fact
            "fact.g"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

SET(parser_srcs
    "${CMAKE_CURRENT_SOURCE_DIR}/factparser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/factvisitor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/factdefaultvisitor.cpp"
)

SET_SOURCE_FILES_PROPERTIES(
    "${CMAKE_CURRENT_SOURCE_DIR}/factast.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/factparser.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/factparser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/factvisitor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/factvisitor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/factdefaultvisitor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/factdefaultvisitor.cpp"
    GENERATED
    )


SET(assembled_parser_srcs
    factlexer.cpp
    debugvisitor.cpp
)


# add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -O2)

# tell CMake to generate the executable
ADD_EXECUTABLE(fact-parser ${assembled_parser_srcs} ${parser_srcs} main.cpp)

target_link_libraries(fact-parser ${QT_QTCORE_LIBRARY})

# in order to generate only the parser, call "make parser"
ADD_CUSTOM_TARGET(parser echo "Generating the parser"
    DEPENDS ${parser_srcs}
    )

# if you want it generated even if the file hasn't changed (but kdev-pg has,
# for example) then call "make parser-clean && make parser"
ADD_CUSTOM_TARGET(parser-clean echo "Cleaning up parser files")
ADD_CUSTOM_COMMAND(TARGET parser-clean
    PRE_BUILD
    COMMAND rm -f ${parser_srcs}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
