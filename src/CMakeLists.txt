set(KDEVELOP_PG_QT_INSTALL_INCLUDEDIR "${KDE_INSTALL_INCLUDEDIR}/KDevelopPGQt")

add_subdirectory(include)

# tell CMake to generate the executable
add_executable(kdev-pg-qt)
add_executable(KDevelopPGQt::kdev-pg-qt ALIAS kdev-pg-qt)

ecm_mark_nongui_executable(kdev-pg-qt)

kde_enable_exceptions()

target_include_directories(kdev-pg-qt PRIVATE
    3rdparty/libastyle
)

target_sources(kdev-pg-qt PRIVATE
    unidata.qrc
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
if (BISON_FOUND)
    bison_target(kdev_pg_parser
        "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-parser.yy"
        "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.cc"
        DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.hh"
        # line info mostly not helpful, also avoids "warning: style of line directive is a GCC extension"
        COMPILE_FLAGS "--no-lines"
    )

    set(parser_src ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.cc)
    # workaround CMP0100 being OLD with currently min required CMake 3.16. Remove once unneeded.
    set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-parser.hh
        PROPERTIES
            SKIP_AUTOMOC ON
    )
else()
    message("'bison' was not found!")
    message("Assuming existence of the generated parser files kdev-pg-parser.[hh,cc]")
    set(parser_src ${CMAKE_CURRENT_SOURCE_DIR}/generated/kdev-pg-parser.cc)
endif()

if (FLEX_FOUND)
    flex_target(kdev_pg_lexer
        "${CMAKE_CURRENT_SOURCE_DIR}/kdev-pg-lexer.ll"
        "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-lexer.cc"
        COMPILE_FLAGS "--yymore --nounistd"
    )
    set(lexer_src ${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-lexer.cc)
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

set(CMAKECONFIG_INSTALL_DIR ${KDE_INSTALL_CMAKEPACKAGEDIR}/KDevelopPGQt)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KDevelopPGQtConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KDevelopPGQtConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

ecm_setup_version(${kdevelop-pg-qt_VERSION}
    VARIABLE_PREFIX KDEVELOP_PG_QT
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kdevelop-pg-qt_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KDevelopPGQtConfigVersion.cmake"
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/kdevelop-pg-qt_version.h"
    DESTINATION "${KDEVELOP_PG_QT_INSTALL_INCLUDEDIR}"
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KDevelopPGQtConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KDevelopPGQtConfigVersion.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/KDevelopPGQtMacros.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
)
install(EXPORT KDevelopPGQtTargets
    FILE        KDevelopPGQtTargets.cmake
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    NAMESPACE KDevelopPGQt::
)

# < 2.4 backward compat
if (BUILD_COMPAT_CMAKECONFIG)

set(CMAKECONFIG_COMPAT_INSTALL_DIR ${KDE_INSTALL_CMAKEPACKAGEDIR}/KDevelop-PG-Qt)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KDevelop-PG-QtConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KDevelop-PG-QtConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_COMPAT_INSTALL_DIR}
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/KDevelop-PG-QtConfigVersion.cmake"
    VERSION ${kdevelop-pg-qt_VERSION}
    COMPATIBILITY AnyNewerVersion
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KDevelop-PG-QtConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KDevelop-PG-QtConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_COMPAT_INSTALL_DIR}"
)

endif()
