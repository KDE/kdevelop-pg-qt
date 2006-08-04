
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})


# autogenerate the lexer and the two parsers (csharp and csharp_pp)

SET(parser_srcs)

FIND_PROGRAM(FLEX_EXECUTABLE
    NAMES flex
    PATHS /usr/bin
    DOC "Flex executable")


# Add commands to generate the parsers.
ADD_CUSTOM_COMMAND(
    OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/csharp.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp.h"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/csharp.g"
    COMMAND ${CMAKE_BINARY_DIR}/src/kdev-pg
    ARGS    --output=csharp
            "csharp.g"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
ADD_CUSTOM_COMMAND(
    OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp.h"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp.g"
    COMMAND ${CMAKE_BINARY_DIR}/src/kdev-pg
    ARGS    --output=csharp_pp
            "csharp_pp.g"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

SET(parser_srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/csharp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp.cpp)

SET_SOURCE_FILES_PROPERTIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/csharp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/csharp.h
    ${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp.h
    GENERATED
    )

IF(FLEX_EXECUTABLE)
    # Add command to generate the lexer.
    ADD_CUSTOM_COMMAND(
        OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.cc"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.ll"
                "${CMAKE_CURRENT_SOURCE_DIR}/csharp.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp.h"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    -o"csharp_lexer.cc"
                "csharp_lexer.ll"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

    SET(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.cc ${parser_srcs})

    SET_SOURCE_FILES_PROPERTIES(
        ${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.cc
        GENERATED
        )
ELSE(FLEX_EXECUTABLE)
    MESSAGE("Assuming existence of the generated lexer file csharp_lexer.cc")
    SET(parser_srcs ${parser_srcs} ${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.cc)
ENDIF(FLEX_EXECUTABLE)


SET(assembled_parser_srcs
    ${parser_srcs}
    decoder.cpp
    csharp_io.cpp
    csharp_pp_scope.cpp
    csharp_pp_handler_visitor.cpp
)


# add definitions, compiler switches, etc.
ADD_DEFINITIONS(-Wall -O2)

# tell CMake to generate the executable
ADD_EXECUTABLE(csharp-parser ${assembled_parser_srcs} main.cpp)

# in order to generate only the parser, call "make parser"
ADD_CUSTOM_TARGET(parser echo "Generating the parser"
    DEPENDS ${parser_srcs}
    )

# if you want it generated even if the file hasn't changed (but kdev-pg has,
# for example) then call "make parser/force"
ADD_CUSTOM_TARGET(parser/force echo "Generating the parser"
    COMMAND rm csharp.cpp csharp_pp.cpp
    DEPENDS ${parser_srcs}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

# if you want it generated even if the file hasn't changed (but kdev-pg has,
# for example) then call "make parser/force"
ADD_CUSTOM_TARGET(parser/force echo "Generating the parser"
    DEPENDS ${parser_srcs}
    )
ADD_CUSTOM_COMMAND(TARGET parser/force
    PRE_BUILD
    COMMAND rm csharp.cpp csharp_pp.cpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
