
PROJECT(cool_parser)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
REMOVE_DEFINITIONS(-DQT_NO_STL)
ADD_DEFINITIONS(-DQT_STL)


# autogenerate the lexer and the parser

SET(parser_srcs)

SET(KDEVPGQT_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/../../kdev-pg/kdev-pg-qt)
SET(KDEVPGQT_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../../../include)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/modules/FindKDevelop-PG-Qt.cmake)
kdevpgqt_generate(parser_srcs cool NAMESPACE cool
    "${CMAKE_CURRENT_SOURCE_DIR}/cool.g"
)


IF(FLEX_EXECUTABLE)
    # Add command to generate the lexer.
    ADD_CUSTOM_COMMAND(
        OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.ll"
                "${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/coolparser.h"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    -o"cool_lexer.cpp"
                "cool_lexer.ll"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

    SET(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.cpp ${parser_srcs})

    SET_SOURCE_FILES_PROPERTIES(
        ${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.cpp
        GENERATED
        )
ELSE(FLEX_EXECUTABLE)
    MESSAGE("--- Assuming existence of the generated lexer file cool_lexer.cpp")
    SET(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.cpp ${parser_srcs})
ENDIF(FLEX_EXECUTABLE)


SET(assembled_parser_srcs
    ${parser_srcs}
    decoder.cpp
    cool_io.cpp
)


# add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -O2)

# tell CMake to generate the executable
ADD_EXECUTABLE(cool-parser ${assembled_parser_srcs} main.cpp)

TARGET_LINK_LIBRARIES( cool-parser ${QT_QTCORE_LIBRARY})

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
