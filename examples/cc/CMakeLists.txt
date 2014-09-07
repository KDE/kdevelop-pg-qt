
PROJECT(cc_parser)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
ADD_DEFINITIONS(-DQT_NO_STL)


# autogenerate the lexer and the parser

SET(parser_srcs)

FIND_PROGRAM(FLEX_EXECUTABLE
    NAMES flex
    PATHS /usr/bin
    DOC "Flex executable")


SET(KDEVPGQT_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/../../kdev-pg/kdev-pg-qt)
SET(KDEVPGQT_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../../../include)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/modules/KDevelop-PG-QtConfig.cmake)
kdevpgqt_generate(parser_srcs cc NAMESPACE cc
    "${CMAKE_CURRENT_SOURCE_DIR}/cc.g"
)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

IF(FLEX_EXECUTABLE)
    # Add command to generate the lexer.
    ADD_CUSTOM_COMMAND(
        OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/cclexer.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cc.ll"
                "${CMAKE_CURRENT_SOURCE_DIR}/FlexLexer.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ccparser.h"
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

TARGET_LINK_LIBRARIES( cc-parser Qt5::Core)
