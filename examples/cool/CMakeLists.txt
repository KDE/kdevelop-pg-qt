remove_definitions(-DQT_NO_STL)
add_definitions(-DQT_STL)

# autogenerate the lexer and the parser

set(parser_srcs)

set(KDEVPGQT_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/../../kdev-pg/kdev-pg-qt)
set(KDEVPGQT_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../../../include)
include(${CMAKE_CURRENT_BINARY_DIR}/../../KDevelop-PG-QtConfig.cmake)
kdevpgqt_generate(parser_srcs cool NAMESPACE cool
    "${CMAKE_CURRENT_SOURCE_DIR}/cool.g"
)


if(FLEX_EXECUTABLE)
    # Add command to generate the lexer.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.ll"
                "${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.h"
                "${CMAKE_CURRENT_BINARY_DIR}/coolparser.h"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    -o"cool_lexer.cpp"
                "cool_lexer.ll"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

    set(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.cpp ${parser_srcs})

    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.cpp
        PROPERTIES
            GENERATED TRUE
            SKIP_AUTOMOC ON
        )
else()
    message("--- Assuming existence of the generated lexer file cool_lexer.cpp")
    set(parser_srcs ${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.cpp ${parser_srcs})
endif()


set(assembled_parser_srcs
    ${parser_srcs}
    decoder.cpp
    cool_io.cpp
)


# add definitions, compiler switches, etc.
add_definitions(-Wall -O2)

# tell CMake to generate the executable
add_executable(cool-parser ${assembled_parser_srcs} main.cpp)

target_link_libraries( cool-parser Qt6::Core)
