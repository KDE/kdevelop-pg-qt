# add definitions, compiler switches, etc.
add_definitions(-Wall -O2)

# tell CMake to generate the executable
add_executable(cool-parser)

# autogenerate the lexer and the parser

kdevpgqt_generate(cool-parser cool NAMESPACE cool
    "${CMAKE_CURRENT_SOURCE_DIR}/cool.g"
)

if(FLEX_EXECUTABLE)
    # Add command to generate the lexer.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/generated/cool_lexer.cpp"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.ll"
                "${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.h"
                "${CMAKE_CURRENT_BINARY_DIR}/coolparser.h"
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    -o"generated/cool_lexer.cpp"
                "cool_lexer.ll"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

    target_sources(cool-parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/generated/cool_lexer.cpp)
    target_include_directories(cool-parser PRIVATE ${FLEX_INCLUDE_DIRS})

    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/cool_lexer.cpp
        PROPERTIES
            GENERATED TRUE
            SKIP_AUTOMOC ON
        )
else()
    message("--- Assuming existence of the generated lexer file cool_lexer.cpp")
    target_sources(cool-parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/generated/cool_lexer.cpp)
    target_include_directories(cool-parser PRIVATE 3rdparty)
endif()

target_sources(cool-parser PRIVATE
    main.cpp
    decoder.cpp
    cool_io.cpp
)

target_link_libraries(cool-parser
    KDevelopPGQt::Utils
    Qt6::Core
)
