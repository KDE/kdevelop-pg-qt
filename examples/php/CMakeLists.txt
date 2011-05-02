project(php_lexer)  

set(parser_STAT_SRCS
  phptest.cpp
)

# Add command to generate the parser.
ADD_CUSTOM_COMMAND(
  OUTPUT  "${CMAKE_CURRENT_SOURCE_DIR}/phpast.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/phpparser.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/phpparser.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/phpvisitor.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/phpvisitor.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/phpdefaultvisitor.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/phpdefaultvisitor.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/phpdebugvisitor.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/phplexer.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/phplexer.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/tokentext.h"
  DEPENDS 
  "${CMAKE_CURRENT_SOURCE_DIR}/php.g"
  COMMAND ${CMAKE_CURRENT_BINARY_DIR}/../../kdev-pg/kdev-pg-qt
  ARGS    --output=php --namespace=Php --debug-visitor --automata --token-text
  "php.g"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

SET(parser_SRCS
"${CMAKE_CURRENT_SOURCE_DIR}/phpparser.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/phpvisitor.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/phpdefaultvisitor.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/phplexer.cpp")

add_executable( phptest ${parser_SRCS} ${parser_STAT_SRCS} )
target_link_libraries( phptest
${QT_QTCORE_LIBRARY}
)

