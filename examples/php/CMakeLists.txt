add_definitions(-fexceptions)

add_executable(phptest)

target_sources(phptest PRIVATE
    phptest.cpp
)

kdevpgqt_generate(phptest php NAMESPACE Php DEBUG_VISITOR TOKEN_TEXT GENERATE_LEXER
    "${CMAKE_CURRENT_SOURCE_DIR}/php.g"
)

target_link_libraries(phptest
    KDevelopPGQt::Utils
    Qt6::Core
)
