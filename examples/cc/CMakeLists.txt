
PROJECT(cc_parser)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
ADD_DEFINITIONS(-DQT_NO_STL)


# autogenerate the lexer and the parser

SET(parser_srcs)

FIND_PROGRAM(FLEX_EXECUTABLE
    NAMES flex
    PATHS /usr/bin
    DOC "Flex executable")


# Add command to generate the parser.
ADD_CUSTOM_COMMAND(
    OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/ccast.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/ccparser.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/ccparser.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/ccvisitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/ccvisitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/ccdefaultvisitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/ccdefaultvisitor.cpp"
    DEPENDS 
            "${CMAKE_CURRENT_SOURCE_DIR}/lexer.h"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/../../kdev-pg/kdev-pg-qt
    ARGS    --output=cc
            "cc.g"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

SET(parser_srcs
    "${CMAKE_CURRENT_SOURCE_DIR}/ccparser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ccvisitor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ccdefaultvisitor.cpp")

SET_SOURCE_FILES_PROPERTIES(
    "${CMAKE_CURRENT_SOURCE_DIR}/ccast.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ccparser.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ccparser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ccvisitor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ccvisitor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ccdefaultvisitor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/ccdefaultvisitor.cpp"
    GENERATED
    )


IF(FLEX_EXECUTABLE)
    # Add command to generate the lexer.
    ADD_CUSTOM_COMMAND(
        OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/cclexer.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cc.ll"
                "${CMAKE_CURRENT_SOURCE_DIR}/FlexLexer.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/ccparser.h"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    -o"cclexer.cpp"
                "cc.ll"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

    SET(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/cclexer.cpp ${parser_srcs})

    SET_SOURCE_FILES_PROPERTIES(
        ${CMAKE_CURRENT_SOURCE_DIR}/cclexer.cpp
        GENERATED
        )
ELSE(FLEX_EXECUTABLE)
    MESSAGE("--- Assuming existence of the generated lexer file cclexer.cpp")
    SET(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/cclexer.cpp ${parser_srcs})
ENDIF(FLEX_EXECUTABLE)


SET(cc_parser_srcs
    ${parser_srcs}
    main.cpp
    dumptree.cpp
)


# add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -O2)

# tell CMake to generate the executable
ADD_EXECUTABLE(cc-parser ${cc_parser_srcs})

TARGET_LINK_LIBRARIES( cc-parser ${QT_QTCORE_LIBRARY} kdecore)

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
