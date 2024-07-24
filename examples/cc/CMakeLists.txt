# add definitions, compiler switches, etc.
add_definitions(-DQT_NO_STL)
add_definitions(-Wall -O2)

# tell CMake to generate the executable
add_executable(cc-parser)

# autogenerate the lexer and the parser
set(KDEVPGQT_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/../../bin/kdev-pg-qt)
set(KDEVPGQT_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../../../include)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../KDevelop-PG-QtMacros.cmake)
kdevpgqt_generate(cc-parser cc NAMESPACE cc
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

    target_sources(cc-parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cclexer.cpp)

    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/cclexer.cpp
        PROPERTIES
            GENERATED TRUE
            SKIP_AUTOMOC ON
        )
else()
    message("--- Assuming existence of the generated lexer file cclexer.cpp")
    target_sources(cc-parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cclexer.cpp)
endif()

target_sources(cc-parser PRIVATE
    main.cpp
    dumptree.cpp
)

target_link_libraries( cc-parser Qt6::Core)
