#
# Find the KDevelop Parser Generator and set various variables accordingly
#
# KDEVPG_DIR and can be set to adjust the directory where the kdevelop-pg
# headers and executable are searched. This should point to the installation
# directory of kdevelop-pg
#
# KDEVPG_FOUND - set to TRUE if KDevelop-PG was found FALSE otherwise
#
# KDEVPG_INCLUDE_DIR         - include dir of kdevelop-pg, for example /usr/include/kdevelop-pg
#                              can be set by the user to select different include dirs
# KDEVPG_EXECUTABLE          - the absolute path to the kdevelop-pg executable
#
# KDEVPG_GENERATE(SRC_FILE_VAR OUTPUT language [NAMESPACE ns] GRAMMARFILE ADDITIONALDEPS)
#     macro to add a custom target for the generation of the parser
#     OUTPUT will be given to kdev-pg as the --output parameter and thus sets the filename prefix
#     NAMESPACE can be given to choose a namespace different from the OUTPUT value
#     Note: The macro only exists when KDEVPG was found
#
# Copyright (c) 2007 Andreas Pakulat <apaku@gmx.de>
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if( KDEVPG_INCLUDE_DIR AND KDEVPG_EXECUTABLE )
    set(KDevelop-PG_FIND_QUIETLY TRUE)
endif( KDEVPG_INCLUDE_DIR AND KDEVPG_EXECUTABLE )

if(WIN32)
    file(TO_CMAKE_PATH "$ENV{PROGRAMFILES}" _progFiles)
    set(_KDEVPG_DIR ${_progFiles}/kdevelop-pg)
endif(WIN32)

if( NOT KDEVPG_DIR )
    find_path( _kdevpgIncDir kdevelop-pg/kdev-pg-token-stream.h
        PATHS
        ${CMAKE_INSTALL_PREFIX}/include
        ${_KDEVPG_DIR}/include
    )
    set(KDEVPG_INCLUDE_DIR ${_kdevpgIncDir}/kdevelop-pg)
    find_program( KDEVPG_EXECUTABLE NAMES kdev-pg
        PATHS
        ${CMAKE_INSTALL_PREFIX}/bin
        ${_KDEVPG_DIR}/bin
    )
else( NOT KDEVPG_DIR )
    find_path( _kdevpgIncDir kdevelop-pg/kdev-pg-token-stream.h
        PATHS
        ${CMAKE_INSTALL_PREFIX}/include
        ${_KDEVPG_DIR}/include
	${KDEVPG_DIR}/include
    )
    set(KDEVPG_INCLUDE_DIR ${_kdevpgIncDir}/kdevelop-pg)
    find_program( KDEVPG_EXECUTABLE NAMES kdev-pg
        PATHS
        ${CMAKE_INSTALL_PREFIX}/bin
        ${_KDEVPG_DIR}/bin
	${KDEVPG_DIR}/bin
    )
endif( NOT KDEVPG_DIR )
set(KDEVPG_INCLUDE_DIR ${KDEVPG_INCLUDE_DIR} CACHE PATH "kdevelop-pg include directory containing the headers")
set( KDEVPG_EXECUTABLE ${KDEVPG_EXECUTABLE} CACHE PATH "executable for kdevelop-pg" )

if( KDEVPG_INCLUDE_DIR
 AND KDEVPG_EXECUTABLE)

    if( NOT KDevelop-PG_FIND_QUIETLY )
        message(STATUS "Found KDevelop-PG")
    endif( NOT KDevelop-PG_FIND_QUIETLY )

# if all modules found
    set(KDEVPG_FOUND TRUE)

    macro(KDEVPG_GENERATE _srcVar _language )
        set(_depList ${ARGN})
	list(GET _depList 0 _ns)
        set(_namespace ${ARGV1})
	if( ${_ns} STREQUAL "NAMESPACE" )
            list(GET _depList 1 _namespace)
            list(GET _depList 2 _grammarFile)
            list(REMOVE_AT _depList 0 1 2)
        else( ${_ns} STREQUAL "NAMESPACE" )
            list(GET _depList 0 _grammarFile)
            list(REMOVE_AT _depList 0)
	endif( ${_ns} STREQUAL "NAMESPACE" )
        if(NOT _grammarFile)
            message(ERROR "No grammar file given to KDEVPG_GENERATE macro")
        endif(NOT _grammarFile)
        add_custom_command(
            OUTPUT  "${CMAKE_CURRENT_BINARY_DIR}/${_language}_ast.h"
                    "${CMAKE_CURRENT_BINARY_DIR}/${_language}_parser.h"
                    "${CMAKE_CURRENT_BINARY_DIR}/${_language}_parser.cpp"
                    "${CMAKE_CURRENT_BINARY_DIR}/${_language}_visitor.h"
                    "${CMAKE_CURRENT_BINARY_DIR}/${_language}_visitor.cpp"
                    "${CMAKE_CURRENT_BINARY_DIR}/${_language}_default_visitor.h"
                    "${CMAKE_CURRENT_BINARY_DIR}/${_language}_default_visitor.cpp"
            MAIN-DEPENDECY "${_grammarFile}"
	    DEPENDS ${_depList}
            COMMAND ${KDEVPG_EXECUTABLE}
            ARGS    --output=${_language} --namespace=${_namespace}
                    "${_grammarFile}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        )
    
        set( ${_srcVar}
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_parser.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_visitor.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_default_visitor.cpp" )
    endmacro(KDEVPG_GENERATE)

else( KDEVPG_INCLUDE_DIR
 AND KDEVPG_EXECUTABLE)

    if( KDevelop-PG_FIND_REQUIRED)
        message(FATAL_ERROR "Couldn't find KDevelop-PG.")
    else( KDevelop-PG_FIND_REQUIRED)
        message(STATUS "Couldn't find KDevelop-PG.")
    endif( KDevelop-PG_FIND_REQUIRED)
    message(STATUS "You can set KDEVPG_DIR to help cmake find KDevelop-PG")
    set(KDEVPG_FOUND FALSE)

endif( KDEVPG_INCLUDE_DIR
 AND KDEVPG_EXECUTABLE)

if(KDEVPG_FOUND)
message(STATUS "Using kdevelop-pg include dir: ${KDEVPG_INCLUDE_DIR}")
message(STATUS "Using kdevelop-pg executable: ${KDEVPG_EXECUTABLE}")
endif(KDEVPG_FOUND)


