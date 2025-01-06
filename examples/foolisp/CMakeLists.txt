add_executable(foolisptest)

target_sources(foolisptest PRIVATE
    foolisptest.cpp
)

kdeveloppgqt_generate(foolisptest foolisp NAMESPACE FooLisp DEBUG_VISITOR TOKEN_TEXT GENERATE_LEXER
    "${CMAKE_CURRENT_SOURCE_DIR}/foolisp.g"
)

target_link_libraries(foolisptest
    KDevelopPGQt::Utils
    Qt6::Core
)
