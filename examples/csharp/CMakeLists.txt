
PROJECT(csharp_parser)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})


# autogenerate the lexer, the two parsers (csharp and csharp_pp)
# and the KDevelop codemodel

SET(parser_srcs)
SET(codemodel_srcs)

FIND_PROGRAM(FLEX_EXECUTABLE
    NAMES flex
    PATHS /usr/bin
    DOC "Flex executable")

FIND_PROGRAM(KDEVCMG_EXECUTABLE
    NAMES kdev-cmg
    PATHS ${CMAKE_BINARY_DIR}/kdev-cmg /usr/bin
    DOC "kdev-cmg executable")


# Add commands to generate the parsers.
ADD_CUSTOM_COMMAND(
    OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/csharp_ast.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_parser.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_parser.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_visitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_visitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_default_visitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_default_visitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_serialize_visitor.h"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/csharp.g"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.h"
    COMMAND ${CMAKE_BINARY_DIR}/kdev-pg/kdev-pg
    ARGS    --output=csharp
            --serialize-visitor
            "csharp.g"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
ADD_CUSTOM_COMMAND(
    OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_ast.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_parser.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_parser.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_visitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_visitor.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_default_visitor.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_default_visitor.cpp"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp.g"
            "${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.h"
    COMMAND ${CMAKE_BINARY_DIR}/kdev-pg/kdev-pg
    ARGS    --output=csharp_pp
            "csharp_pp.g"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

SET(parser_srcs
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_parser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_visitor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_default_visitor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_parser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_visitor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_default_visitor.cpp")

SET_SOURCE_FILES_PROPERTIES(
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_ast.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_parser.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_parser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_visitor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_visitor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_default_visitor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_default_visitor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_serialize_visitor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_ast.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_parser.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_parser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_visitor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_visitor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_default_visitor.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_default_visitor.cpp"
    GENERATED
    )

IF(FLEX_EXECUTABLE)
    # Add command to generate the lexer.
    ADD_CUSTOM_COMMAND(
        OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.ll"
                "${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/csharp_parser.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/csharp_pp_parser.h"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    -o"csharp_lexer.cpp"
                "csharp_lexer.ll"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

    SET(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.cpp ${parser_srcs})

    SET_SOURCE_FILES_PROPERTIES(
        "${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.cpp"
        GENERATED
        )
ELSE(FLEX_EXECUTABLE)
    MESSAGE("--- Assuming existence of the generated lexer file csharp_lexer.cpp")
    SET(parser_srcs ${parser_srcs} ${CMAKE_CURRENT_SOURCE_DIR}/csharp_lexer.cpp)
ENDIF(FLEX_EXECUTABLE)


IF(KDEVCMG_EXECUTABLE)
    # Add command to generate the code model
    ADD_CUSTOM_COMMAND(
        OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel_fwd.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel_chameleon.h"
                "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel_chameleon.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel.cm"
        COMMAND ${KDEVCMG_EXECUTABLE}
        ARGS    --language=csharp
                "csharp_codemodel.cm"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

    SET(codemodel_srcs "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel.cpp")

    SET_SOURCE_FILES_PROPERTIES(
        "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel_fwd.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel_chameleon.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel_chameleon.cpp"
        GENERATED
        )
ELSE(KDEVCMG_EXECUTABLE)
    MESSAGE("--- Assuming existence of the generated codemodel files")
    SET(codemodel_srcs
        "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/csharp_codemodel_chameleon.cpp")
ENDIF(KDEVCMG_EXECUTABLE)



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
ADD_EXECUTABLE(csharp-serializer ${assembled_parser_srcs} main_serialize.cpp)

# in order to generate only the parser, call "make parser"
ADD_CUSTOM_TARGET(parser echo "Generating the parser"
    DEPENDS ${parser_srcs}
    )

# if you want it generated even if the file hasn't changed (but kdev-pg has,
# for example) then call "make parser-clean && make parser"
ADD_CUSTOM_TARGET(parser-clean echo "Generating the parser")
ADD_CUSTOM_COMMAND(TARGET parser-clean
    PRE_BUILD
    COMMAND rm -f ${parser_srcs}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )


# in order to generate only the codemodel, call "make codemodel"
ADD_CUSTOM_TARGET(codemodel echo "Generating the codemodel"
    DEPENDS ${codemodel_srcs}
    )

# if you want it generated even if the file hasn't changed (but kdev-cmg has,
# for example) then call "make codemodel-clean && make codemodel"
ADD_CUSTOM_TARGET(codemodel-clean echo "Generating the codemodel")
ADD_CUSTOM_COMMAND(TARGET codemodel-clean
    PRE_BUILD
    COMMAND rm -f ${codemodel_srcs}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
