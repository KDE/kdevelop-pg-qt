#
# Find the KDevelop Parser Generator and set various variables accordingly
#
# KDEVPG_DIR and can be set to adjust the directory where the kdevelop-pg-qt
# headers and executable are searched. This should point to the installation
# directory of kdevelop-pg-qt
#
# KDEVPGQT_FOUND - set to TRUE if KDevelop-PG was found FALSE otherwise
#
# KDEVPGQT_INCLUDE_DIR         - include dir of kdevelop-pg, for example /usr/include/kdevelop-pg
#                              can be set by the user to select different include dirs
# KDEVPGQT_EXECUTABLE          - the absolute path to the kdevelop-pg executable
#
# KDEVPGQT_GENERATE(SRC_FILE_VAR OUTPUT language 
#                     [NAMESPACE ns] [DEBUG_VISITOR] [DUMP_INFO] 
#                     GRAMMARFILE ADDITIONALDEPS)
#     macro to add a custom target for the generation of the parser
#     OUTPUT will be given to kdev-pg as the --output parameter and thus sets the filename prefix
#     NAMESPACE can be given to choose a namespace different from the OUTPUT value
#     DEBUG_VISITOR will run kdevelop-pg with the --debug-visitor argument to generate a simple
#                   visitor that will print debug messages
#     DUMP_INFO will tell kdevelop-pg to dump extra information about symbols, terminals and rules
#               into files in the binary dir
#     Note: The macro only exists when KDEVPG was found
#
# Copyright (c) 2007 Andreas Pakulat <apaku@gmx.de>
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if( KDEVPGQT_INCLUDE_DIR AND KDEVPGQT_EXECUTABLE )
    set(KDevelop-PG-Qt_FIND_QUIETLY TRUE)
endif( KDEVPGQT_INCLUDE_DIR AND KDEVPGQT_EXECUTABLE )

if(WIN32)
    file(TO_CMAKE_PATH "$ENV{PROGRAMFILES}" _progFiles)
    set(_KDEVPGQT_DIR ${_progFiles}/kdevelop-pg-qt)
endif(WIN32)

if( NOT KDEVPGQT_DIR )
    find_path( _kdevpgqtIncDir kdevelop-pg-qt/kdev-pg-token-stream.h
        PATHS
        ${CMAKE_INSTALL_PREFIX}/include
        ${_KDEVPG_DIR}/include
    )
    if( _kdevpgqtIncDir )
        set(KDEVPGQT_INCLUDE_DIR ${_kdevpgIncDir}/kdevelop-pg-qt)
    endif( _kdevpgqtIncDir )
    find_program( KDEVPGQT_EXECUTABLE NAMES kdev-pg-qt
        PATHS
        ${CMAKE_INSTALL_PREFIX}/bin
        ${_KDEVPG_DIR}/bin
    )
    set(KDEVPGQT_INCLUDE_DIR ${KDEVPG_INCLUDE_DIR} CACHE PATH "kdevelop-pg-qt include directory containing the headers")
    set( KDEVPGQT_EXECUTABLE ${KDEVPG_EXECUTABLE} CACHE PATH "executable for kdevelop-pg-qt" )
else( NOT KDEVPGQT_DIR )
    find_path( _kdevpgqtIncDir kdevelop-pg-qt/kdev-pg-token-stream.h
        PATHS
        ${CMAKE_INSTALL_PREFIX}/include
        ${_KDEVPG_DIR}/include
	${KDEVPGQT_DIR}/include
    )
    set(KDEVPGQT_INCLUDE_DIR ${_kdevpgIncDir}/kdevelop-pg-qt)
    find_program( KDEVPGQT_EXECUTABLE NAMES kdev-pg-qt
        PATHS
        ${CMAKE_INSTALL_PREFIX}/bin
        ${_KDEVPG_DIR}/bin
	${KDEVPGQT_DIR}/bin
    )
    set(KDEVPGQT_INCLUDE_DIR ${KDEVPG_INCLUDE_DIR} CACHE PATH "kdevelop-pg-qt include directory containing the headers")
    set( KDEVPGQT_EXECUTABLE ${KDEVPG_EXECUTABLE} CACHE PATH "executable for kdevelop-pg-qt" )
endif( NOT KDEVPGQT_DIR )
if( KDEVPGQT_INCLUDE_DIR
 AND KDEVPGQT_EXECUTABLE)

    if( NOT KDevelop-PG-Qt_FIND_QUIETLY )
        message(STATUS "Found KDevelop-PG-Qt")
    endif( NOT KDevelop-PG-Qt_FIND_QUIETLY )

# if all modules found
    set(KDEVPGQT_FOUND TRUE)

    macro(KDEVPGQT_GENERATE _srcVar _language )
        set(_outputList 
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_ast.h"
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_parser.h"
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_parser.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_visitor.h"
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_visitor.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_default_visitor.h"
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_default_visitor.cpp"
        )
        set(_depList ${ARGN})
	list(GET _depList 0 _ns)
        set(_namespace ${ARGV1})
        if( ${_ns} STREQUAL "NAMESPACE" )
            list(GET _depList 1 _namespace)
            list(REMOVE_AT _depList 0 1)
        endif( ${_ns} STREQUAL "NAMESPACE" )
	list(GET _depList 0 _dbg)
	set(_dbgVisit)
        if( ${_dbg} STREQUAL "DEBUG_VISITOR" )
            list(REMOVE_AT _depList 0)
	    set(_dbgVisit "--debug-visitor")
	    set(_outputList ${_outputList}
                "${CMAKE_CURRENT_BINARY_DIR}/${_language}_debug_visitor.h"
            )
	endif(${_dbg} STREQUAL "DEBUG_VISITOR" )
	set(_dumpInfo)
	list(GET _depList 0 _dump)
	if( ${_dump} STREQUAL "DUMP_INFO" )
            list(REMOVE_AT _depList 0)
	    set(_dumpInfo --terminals --symbols --rules)
	    set(_outputList ${_outputList} 
                "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-terminals"
                "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-symbols"
                "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-rules"
            )
	endif( ${_dump} STREQUAL "DUMP_INFO" )

        list(GET _depList 0 _grammarFile)
        list(REMOVE_AT _depList 0)
        if(NOT _grammarFile)
            message(ERROR "No grammar file given to KDEVPG_GENERATE macro")
        endif(NOT _grammarFile)
        add_custom_command(
            OUTPUT  ${_outputList}
            MAIN_DEPENDENCY "${_grammarFile}"
	    DEPENDS ${_depList}
            COMMAND ${KDEVPG_EXECUTABLE}
            ARGS    --output=${_language} --namespace=${_namespace}
                    ${_dbgVisit} ${_dumpInfo} "${_grammarFile}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        )
    
        set( ${_srcVar}
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_parser.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_visitor.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/${_language}_default_visitor.cpp" )
    endmacro(KDEVPG_GENERATE)


else( KDEVPGQT_INCLUDE_DIR
 AND KDEVPGQT_EXECUTABLE)

    if( KDevelop-PG-Qt_FIND_REQUIRED)
        message(FATAL_ERROR "Couldn't find KDevelop-PG-Qt.")
    else( KDevelop-PG-Qt_FIND_REQUIRED)
        message(STATUS "Couldn't find KDevelop-PG-Qt.")
    endif( KDevelop-PG-Qt_FIND_REQUIRED)
    message(STATUS "You can set KDEVPGQT_DIR to help cmake find KDevelop-PG")
    set(KDEVPGQT_FOUND FALSE)

endif( KDEVPGQT_INCLUDE_DIR
 AND KDEVPGQT_EXECUTABLE)

if(KDEVPGQT_FOUND)
message(STATUS "Using kdevelop-pg-qt include dir: ${KDEVPGQT_INCLUDE_DIR}")
message(STATUS "Using kdevelop-pg-qt executable: ${KDEVPGQT_EXECUTABLE}")
endif(KDEVPGQT_FOUND)

