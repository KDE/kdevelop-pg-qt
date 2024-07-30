# add definitions, compiler switches, etc.
add_definitions(-Wall -O2)

# tell CMake to generate the executable
add_executable(cool-parser)

# autogenerate the lexer and the parser

kdevpgqt_generate(cool-parser cool NAMESPACE cool
    "${CMAKE_CURRENT_SOURCE_DIR}/cool.g"
)

if (FLEX_FOUND)
    flex_target(cool_lexer
        "${CMAKE_CURRENT_SOURCE_DIR}/cool_lexer.ll"
        "${CMAKE_CURRENT_BINARY_DIR}/cool_lexer.cpp"
    )

    target_sources(cool-parser PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/cool_lexer.cpp)
    target_include_directories(cool-parser PRIVATE ${FLEX_INCLUDE_DIRS})
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
