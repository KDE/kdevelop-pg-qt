find_package(KDevelop-PG-Qt)

# add definitions, compiler switches, etc.
add_definitions(-Wall -O2)

# tell CMake to generate the executable
add_executable(fact-parser)

kdevpgqt_generate(fact-parser fact NAMESPACE fact DEBUG_VISITOR
    "${CMAKE_CURRENT_SOURCE_DIR}/fact.g"
    "${CMAKE_CURRENT_SOURCE_DIR}/factlexer.h"
)

target_sources(fact-parser PRIVATE
    main.cpp
    factlexer.cpp
)

target_link_libraries(fact-parser Qt6::Core)

