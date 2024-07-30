# TODO: fix on windows
if (NOT WIN32)
    add_subdirectory(cc)
    add_subdirectory(cool)
endif()
#add_subdirectory(fact)
add_subdirectory(foolisp)
add_subdirectory(php)
