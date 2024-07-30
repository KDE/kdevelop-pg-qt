# add definitions, compiler switches, etc.
add_definitions(-Wall -O2)

# tell CMake to generate the executable
add_executable(cc-parser)

# autogenerate the lexer and the parser
kdevpgqt_generate(cc-parser cc NAMESPACE cc
    "${CMAKE_CURRENT_SOURCE_DIR}/cc.g"
)

if(FLEX_EXECUTABLE)
    # Add command to generate the lexer.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/cclexer.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cc.ll"
                "${CMAKE_CURRENT_BINARY_DIR}/ccparser.h"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    -o "cclexer.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/cc.ll"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        )

    target_sources(cc-parser PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/cclexer.cpp)
    target_include_directories(cc-parser PRIVATE ${FLEX_INCLUDE_DIRS})

    set_source_files_properties(
        ${CMAKE_CURRENT_BINARY_DIR}/cclexer.cpp
        PROPERTIES
            GENERATED TRUE
            SKIP_AUTOMOC ON
        )
else()
    message("--- Assuming existence of the generated lexer file cclexer.cpp")
    target_sources(cc-parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/generated/cclexer.cpp)
    target_include_directories(cc-parser PRIVATE 3rdparty)
endif()

target_sources(cc-parser PRIVATE
    main.cpp
    dumptree.cpp
)

target_link_libraries(cc-parser
    KDevelopPGQt::Utils
    Qt6::Core
)
