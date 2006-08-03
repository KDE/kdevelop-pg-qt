
PROJECT(kdevpg)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})


SET(kdevpg_srcs
    ASBeautifier.cpp
    ASFormatter.cpp
    kdev-pg.cpp
    kdev-pg-visitor.cpp
    kdev-pg-default-visitor.cpp
    kdev-pg-pretty-printer.cpp
    kdev-pg-global.cpp
    kdev-pg-code-gen.cpp
    kdev-pg-ast-gen.cpp
    kdev-pg-visitor-gen.cpp
    kdev-pg-visitor-bits-gen.cpp
    kdev-pg-default-visitor-gen.cpp
    kdev-pg-beautifier.cpp
    kdev-pg-checker.cpp
    kdev-pg-main.cpp
    kdev-pg-first.cpp
    kdev-pg-follow.cpp
    kdev-pg-clone-tree.cpp)


# Custom support for flex/bison
SET(parser_srcs)

FIND_PROGRAM(FLEX_EXECUTABLE
    NAMES flex
    PATHS /usr/bin
    DOC "Flex executable")

FIND_PROGRAM(BISON_EXECUTABLE
    NAMES bison
    PATHS /usr/bin
    DOC "bison executable")

IF(FLEX_EXECUTABLE)
    # Add command to run the lexer.
    ADD_CUSTOM_COMMAND(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-lexer.cc"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-lexer.ll"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    -o"${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-lexer.cc"
                "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-lexer.ll"
        )

    SET(parser_srcs ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-lexer.cc)
    SET_SOURCE_FILES_PROPERTIES(
        ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-lexer.cc
        GENERATED
        )
ELSE(FLEX_EXECUTABLE)
    MESSAGE("Assuming existence of the generated lexer file kdev-pg-lexer.cc")
    SET(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-lexer.cc)
ENDIF(FLEX_EXECUTABLE)

IF(BISON_EXECUTABLE)
    # Add command to run the parser.
    ADD_CUSTOM_COMMAND(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.cc"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-parser.yy"
                ${parser_srcs}
        COMMAND ${BISON_EXECUTABLE}
        ARGS    -o"${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.cc"
                -d "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-parser.yy"
        )

    SET(parser_srcs ${parser_srcs} ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.cc)
    SET_SOURCE_FILES_PROPERTIES(
        ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.cc
        GENERATED
        )
ELSE(BISON_EXECUTABLE)
    MESSAGE("Assuming existence of the generated parser file kdev-pg-parser.cc")
    SET(parser_srcs ${parser_srcs} ${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-parser.cc)
ENDIF(BISON_EXECUTABLE)


# add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -O2)

# tell CMake to generate the executable
ADD_EXECUTABLE(kdev-pg ${parser_srcs} ${kdevpg_srcs})

# in order to generate only the parser, call "make parser"
ADD_CUSTOM_TARGET(parser echo "Generating the parser"
    DEPENDS ${parser_srcs}
    )
