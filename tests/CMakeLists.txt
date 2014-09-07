include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)

ecm_add_test(testlocationtable.cpp LINK_LIBRARIES Qt5::Core Qt5::Test)
ecm_add_test(testmemorypool.cpp LINK_LIBRARIES Qt5::Core Qt5::Test)
ecm_add_test(benchmarks.cpp LINK_LIBRARIES Qt5::Core Qt5::Test)

