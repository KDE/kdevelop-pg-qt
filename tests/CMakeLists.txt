ecm_add_test(testlocationtable.cpp LINK_LIBRARIES Qt6::Core Qt6::Test)
target_include_directories(testlocationtable PRIVATE ${CMAKE_SOURCE_DIR}/src/include)

ecm_add_test(testmemorypool.cpp LINK_LIBRARIES Qt6::Core Qt6::Test)
target_include_directories(testmemorypool PRIVATE ${CMAKE_SOURCE_DIR}/src/include)

ecm_add_test(benchmarks.cpp LINK_LIBRARIES Qt6::Core Qt6::Test)
target_include_directories(benchmarks PRIVATE ${CMAKE_SOURCE_DIR}/src/include)

