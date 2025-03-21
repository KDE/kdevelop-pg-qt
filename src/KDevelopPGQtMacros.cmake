# SPDX-FileCopyrightText: 2007 Andreas Pakulat <apaku@gmx.de>
#
# SPDX-License-Identifier: BSD-3-Clause
#
# KDEVELOPPGQT_GENERATE(
#     <src_file_var>|<target>
#     <language>
#     [NAMESPACE <ns>]
#     [DEBUG_VISITOR]
#     [TOKEN_TEXT]
#     [DUMP_INFO]
#     [ENFORCE_COMPATIBLE_ERROR_AWARE_CODE]
#     <grammarfile>
#     <additionaldeps>
# )
# This macro to add a custom target for the generation of the parser.
#     <language> will be given to kdev-pg as the --output parameter and thus sets the filename prefix
#     NAMESPACE can be given to choose a namespace different from the OUTPUT value
#     DEBUG_VISITOR will run kdevelop-pg with the --debug-visitor argument to generate a simple
#                   visitor that will print debug messages
#     TOKEN_TEXT will run kdevelop-pg with the --token-text argument to generate a simple
#                function that returns a readable name of a token
#     DUMP_INFO will tell kdevelop-pg to dump extra information about symbols, terminals and rules
#               into files in the binary dir
#     ENFORCE_COMPATIBLE_ERROR_AWARE_CODE will ensure that --compatible-error-aware-code is also
#               passed in case of GCC. By default it only is set for non-GNU compilers.

macro(KDEVELOPPGQT_GENERATE _srcOrTargetVar _language )
    if (TARGET ${_srcOrTargetVar})
        get_target_property(aliased_target ${_srcOrTargetVar} ALIASED_TARGET)
        if(aliased_target)
          message(FATAL_ERROR "Target argument passed to kdeveloppgqt_generate must not be an alias: ${_srcOrTargetVar}")
        endif()
    endif()
    set(_outputList
        "${CMAKE_CURRENT_BINARY_DIR}/${_language}tokentype.h")
    set(_depList ${ARGN})
    set(_astList
        "${CMAKE_CURRENT_BINARY_DIR}/${_language}ast.h")
    set(_parserList
        "${CMAKE_CURRENT_BINARY_DIR}/${_language}parser.h"
        "${CMAKE_CURRENT_BINARY_DIR}/${_language}parser.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/${_language}visitor.h"
        "${CMAKE_CURRENT_BINARY_DIR}/${_language}visitor.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/${_language}defaultvisitor.h"
        "${CMAKE_CURRENT_BINARY_DIR}/${_language}defaultvisitor.cpp")
    set(_lexerList)
    set(_dbgVisit)
    set(_namespace)
    set(_tokenText)
    set(_dumpInfo)
    if(CMAKE_COMPILER_IS_GNUCC)
        set(_beautifulCode)
    else()
        set(_beautifulCode --compatible-error-aware-code)
    endif()
    set(_conflicts)
    while(1)
        list(GET _depList 0 _arg)
        if( ${_arg} STREQUAL "NAMESPACE" )
            list(GET _depList 1 _namespace)
            list(REMOVE_AT _depList 0 1)
            set(_namespace --namespace=${_namespace})
        elseif( ${_arg} STREQUAL "DEBUG_VISITOR" )
            list(REMOVE_AT _depList 0)
            set(_dbgVisit "--debug-visitor")
            set(_outputList ${_outputList}
                "${CMAKE_CURRENT_BINARY_DIR}/${_language}debugvisitor.h"
            )
        elseif( ${_arg} STREQUAL "TOKEN_TEXT" )
            list(REMOVE_AT _depList 0)
            set(_tokenText "--token-text")
            set(_outputList ${_outputList}
                "${CMAKE_CURRENT_BINARY_DIR}/${_language}tokentext.h"
            )
        elseif( ${_arg} STREQUAL "DUMP_INFO" )
            list(REMOVE_AT _depList 0)
            set(_dumpInfo --terminals --symbols --rules)
            set(_outputList ${_outputList}
                "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-terminals"
                "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-symbols"
                "${CMAKE_CURRENT_BINARY_DIR}/kdev-pg-rules"
            )
        elseif( ${_arg} STREQUAL "BEAUTIFUL_CODE" )
            list(REMOVE_AT _depList 0)
            set(_beautifulCode --beautiful-code)
        elseif( ${_arg} STREQUAL "ENFORCE_COMPATIBLE_ERROR_AWARE_CODE" )
            list(REMOVE_AT _depList 0)
            set(_beautifulCode --compatible-error-aware-code)
        elseif( ${_arg} STREQUAL "STRICT_CONFLICTS" )
            list(REMOVE_AT _depList 0)
            set(_conflicts --strict-conflicts)
        elseif( ${_arg} STREQUAL "IGNORE_CONFLICTS" )
            list(REMOVE_AT _depList 0)
            set(_conflicts --ignore-conflicts)
        elseif( ${_arg} STREQUAL "GENERATE_LEXER" )
          list(REMOVE_AT _depList 0)
          set(_lexerList
              "${CMAKE_CURRENT_BINARY_DIR}/${_language}lexer.h"
              "${CMAKE_CURRENT_BINARY_DIR}/${_language}lexer.cpp")
        else()
            break()
        endif()
    endwhile(1)

    set(_outputList ${_outputList} ${_lexerList} ${_astList} ${_parserList})

    list(GET _depList 0 _grammarFile)
    list(REMOVE_AT _depList 0)
    if(NOT _grammarFile)
        message(ERROR "No grammar file given to KDEVELOPPGQT_GENERATE macro")
    endif()
    add_custom_command(
        OUTPUT
                ${_outputList}
        MAIN_DEPENDENCY "${_grammarFile}"
        DEPENDS ${_depList} KDevelopPGQt::kdev-pg-qt
        COMMAND KDevelopPGQt::kdev-pg-qt
        ARGS    --output=${_language} ${_namespace}
                ${_dbgVisit} ${_dumpInfo} ${_beautifulCode} ${_conflicts} "${_grammarFile}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    )
    set_source_files_properties(${_outputList} PROPERTIES
        GENERATED TRUE
        SKIP_AUTOMOC ON
    )
    if(TARGET ${_srcOrTargetVar})
        target_sources(${_srcOrTargetVar} PRIVATE ${_outputList})
    else()
        set( ${_srcOrTargetVar} ${_outputList})
    endif()
endmacro()
