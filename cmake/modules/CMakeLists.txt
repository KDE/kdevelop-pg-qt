# install the cmake files

set(CMAKECONFIG_INSTALL_DIR ${LIB_INSTALL_DIR}/cmake/KDevelop-PG-Qt)
set(cmakeFiles KDevelop-PG-QtConfig.cmake KDevelop-PG-QtConfigVersion.cmake)
install( FILES ${cmakeFiles} DESTINATION ${CMAKECONFIG_INSTALL_DIR} )
