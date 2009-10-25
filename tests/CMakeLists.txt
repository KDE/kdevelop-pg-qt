include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

set(benchmarks_SRCS
    benchmarks.cpp
)
kde4_add_unit_test(benchmarks ${benchmarks_SRCS})
target_link_libraries(benchmarks
    ${QT_QTTEST_LIBRARY}
)
