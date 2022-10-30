INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
REMOVE_DEFINITIONS(-DQT_NO_STL)
ADD_DEFINITIONS(-DQT_STL)

qt_add_resources(kdevpg_rcc_srcs ../unidata.qrc)
kde_enable_exceptions()

SET(kdevpg_srcs
    ASBeautifier.cpp
    ASFormatter.cpp
    ASResource.cpp
    ASEnhancer.cpp
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
IF(BISON_EXECUTABLE)
    # Add command to run the parser.
    ADD_CUSTOM_COMMAND(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.cc"
                "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.hh"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-parser.yy"
        COMMAND ${BISON_EXECUTABLE}
        ARGS    -o "kdev-pg-parser.cc"
                -d "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-parser.yy"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        )

    SET(parser_src ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.cc)
    SET_SOURCE_FILES_PROPERTIES(
        ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.cc
        ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.hh
        PROPERTIES
            GENERATED TRUE
            SKIP_AUTOMOC ON
        )
    SET(OPTIONAL_PARSER_HEADER_DEPENDENCY "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.hh")
ELSE(BISON_EXECUTABLE)
    MESSAGE("'bison' was not found!")
    MESSAGE("Assuming existence of the generated parser files kdev-pg-parser.[hh,cc]")
    SET(parser_src ${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-parser.cc)
    SET(OPTIONAL_PARSER_HEADER_DEPENDENCY "")
ENDIF(BISON_EXECUTABLE)

IF(FLEX_EXECUTABLE)
    # Add command to run the lexer.
    ADD_CUSTOM_COMMAND(
        OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-lexer.cc"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-lexer.ll"
                 ${OPTIONAL_PARSER_HEADER_DEPENDENCY}
        COMMAND ${FLEX_EXECUTABLE}
        ARGS    --yymore --nounistd -o "kdev-pg-lexer.cc"
                "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-lexer.ll"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        )

    SET(lexer_src ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-lexer.cc)
    SET_SOURCE_FILES_PROPERTIES(
        ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-lexer.cc
        PROPERTIES
            GENERATED TRUE
            SKIP_AUTOMOC ON
        )
ELSE(FLEX_EXECUTABLE)
    MESSAGE("'flex' was not found!")
    MESSAGE("Assuming existence of the generated lexer file kdev-pg-lexer.cc")
    SET(lexer_src ${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-lexer.cc)
ENDIF(FLEX_EXECUTABLE)
set_source_files_properties(${lexer_src} PROPERTIES COMPILE_FLAGS "-DYY_NO_INPUT -DYY_NO_UNPUT")


# tell CMake to generate the executable
ADD_EXECUTABLE(kdev-pg-qt ${parser_src} ${lexer_src} ${kdevpg_srcs} ${kdevpg_rcc_srcs})
ecm_mark_nongui_executable(kdev-pg-qt)
TARGET_LINK_LIBRARIES( kdev-pg-qt Qt${QT_MAJOR_VERSION}::Core)
INSTALL(TARGETS kdev-pg-qt DESTINATION bin )

# in order to generate only the parser, call "make parser"
ADD_CUSTOM_TARGET(parser echo "Generating the parser"
    DEPENDS ${parser_src} ${lexer_src}
    )
