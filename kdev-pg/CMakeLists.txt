# tell CMake to generate the executable
add_executable(kdev-pg-qt)
add_executable(KDevelopPGQt::kdev-pg-qt ALIAS kdev-pg-qt)

ecm_mark_nongui_executable(kdev-pg-qt)

kde_enable_exceptions()

target_include_directories(kdev-pg-qt PRIVATE
    3rdparty/libastyle
)

target_sources(kdev-pg-qt PRIVATE
    ../unidata.qrc
    3rdparty/libastyle/ASBeautifier.cpp
    3rdparty/libastyle/ASFormatter.cpp
    3rdparty/libastyle/ASResource.cpp
    3rdparty/libastyle/ASEnhancer.cpp
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
    kdev-pg-default-visitor-bits-gen.cpp
    kdev-pg-serialize-visitor-gen.cpp
    kdev-pg-debug-visitor-gen.cpp
    kdev-pg-new-visitor-gen.cpp
    kdev-pg-new-visitor-bits-gen.cpp
    kdev-pg-token-type-gen.cpp
    kdev-pg-beautifier.cpp
    kdev-pg-checker.cpp
    kdev-pg-inline-checker.cpp
    kdev-pg-main.cpp
    kdev-pg-generate.cpp
    kdev-pg-first.cpp
    kdev-pg-follow.cpp
    kdev-pg-bnf-visitor.cpp
    kdev-pg-clone-tree.cpp
    kdev-pg-regexp.cpp
    kdev-pg-unicode-loader.cpp)


# Custom support for flex/bison
if(BISON_EXECUTABLE)
    # Add command to run the parser.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.cc"
                "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.hh"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-parser.yy"
        COMMAND ${BISON_EXECUTABLE}
        ARGS    -o "kdev-pg-parser.cc"
                -d "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-parser.yy"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        )

    set(parser_src ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.cc)
    set_source_files_properties(
        ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.cc
        ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.hh
        PROPERTIES
            GENERATED TRUE
            SKIP_AUTOMOC ON
        )
    set(OPTIONAL_PARSER_HEADER_DEPENDENCY "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.hh")
else()
    message("'bison' was not found!")
    message("Assuming existence of the generated parser files kdev-pg-parser.[hh,cc]")
    set(parser_src ${CMAKE_CURRENT_SOURCE_DIR}/generated/kdev-pg-parser.cc)
    set(OPTIONAL_PARSER_HEADER_DEPENDENCY "")
endif()

if(FLEX_EXECUTABLE)
    # Add command to run the lexer.
    add_custom_command(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-lexer.cc"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-lexer.ll"
                 ${OPTIONAL_PARSER_HEADER_DEPENDENCY}
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    --yymore --nounistd -o "kdev-pg-lexer.cc"
                "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-lexer.ll"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        )

    set(lexer_src ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-lexer.cc)
    set_source_files_properties(
        ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-lexer.cc
        PROPERTIES
            GENERATED TRUE
            SKIP_AUTOMOC ON
        )
else()
    message("'flex' was not found!")
    message("Assuming existence of the generated lexer file kdev-pg-lexer.cc")
    set(lexer_src ${CMAKE_CURRENT_SOURCE_DIR}/generated/kdev-pg-lexer.cc)
endif()
set_source_files_properties(${lexer_src} PROPERTIES COMPILE_FLAGS "-DYY_NO_INPUT -DYY_NO_UNPUT")

target_link_libraries(kdev-pg-qt
    KDevelopPGQt::Utils
    Qt6::Core
)
install(TARGETS kdev-pg-qt EXPORT KDevelopPGQtTargets DESTINATION ${KDE_INSTALL_BINDIR} )

# in order to generate only the parser, call "make parser"
add_custom_target(parser echo "Generating the parser"
    DEPENDS ${parser_src} ${lexer_src}
    )

target_sources(kdev-pg-qt PRIVATE
    ${parser_src}
    ${lexer_src}
)
