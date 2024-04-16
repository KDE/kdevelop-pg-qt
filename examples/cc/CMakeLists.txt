add_definitions(-DQT_NO_STL)

# autogenerate the lexer and the parser

set(parser_srcs)

find_program(FLEX_EXECUTABLE
    NAMES flex
    PATHS /usr/bin
    DOC "Flex executable")


set(KDEVPGQT_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/../../kdev-pg/kdev-pg-qt)
set(KDEVPGQT_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../../../include)
include(${CMAKE_CURRENT_BINARY_DIR}/../../KDevelop-PG-QtConfig.cmake)
kdevpgqt_generate(parser_srcs cc NAMESPACE cc
    "${CMAKE_CURRENT_SOURCE_DIR}/cc.g"
)

if(FLEX_EXECUTABLE)
    # Add command to generate the lexer.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/cclexer.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cc.ll"
                "${CMAKE_CURRENT_SOURCE_DIR}/FlexLexer.h"
                "${CMAKE_CURRENT_BINARY_DIR}/ccparser.h"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    -o"cclexer.cpp"
                "cc.ll"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

    set(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/cclexer.cpp ${parser_srcs})

    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/cclexer.cpp
        PROPERTIES
            GENERATED TRUE
            SKIP_AUTOMOC ON
        )
else()
    message("--- Assuming existence of the generated lexer file cclexer.cpp")
    set(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/cclexer.cpp ${parser_srcs})
endif()


set(cc_parser_srcs
    ${parser_srcs}
    main.cpp
    dumptree.cpp
)


# add definitions, compiler switches, etc.
add_definitions(-Wall -O2)

# tell CMake to generate the executable
add_executable(cc-parser ${cc_parser_srcs})

target_link_libraries( cc-parser Qt6::Core)
