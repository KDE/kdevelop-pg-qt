add_definitions(-fexceptions)

add_executable(phptest)

target_sources(phptest PRIVATE
    phptest.cpp
)

set(KDEVPGQT_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/../../bin/kdev-pg-qt)

kdevpgqt_generate(phptest php NAMESPACE Php DEBUG_VISITOR TOKEN_TEXT GENERATE_LEXER
    "${CMAKE_CURRENT_SOURCE_DIR}/php.g"
)

target_link_libraries( phptest Qt6::Core)
