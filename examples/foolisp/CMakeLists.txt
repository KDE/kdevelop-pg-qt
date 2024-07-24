add_executable(foolisptest)

target_sources(foolisptest PRIVATE
    foolisptest.cpp
)

set(KDEVPGQT_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/../../bin/kdev-pg-qt)
set(KDEVPGQT_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../../../include)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../KDevelop-PG-QtMacros.cmake)
kdevpgqt_generate(foolisptest foolisp NAMESPACE FooLisp DEBUG_VISITOR TOKEN_TEXT GENERATE_LEXER
    "${CMAKE_CURRENT_SOURCE_DIR}/foolisp.g"
)

target_link_libraries( foolisptest Qt6::Core)
