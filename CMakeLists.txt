# KDEVELOP_PG_QT version
set(KDEVELOP_PG_QT_VERSION_MAJOR 1)
set(KDEVELOP_PG_QT_VERSION_MINOR 90)
set(KDEVELOP_PG_QT_VERSION_PATCH 91)
set(KDEVELOP_PG_QT_VERSION "${KDEVELOP_PG_QT_VERSION_MAJOR}.${KDEVELOP_PG_QT_VERSION_MINOR}.${KDEVELOP_PG_QT_VERSION_PATCH}")

cmake_minimum_required(VERSION 2.8.12)
project(kdevelop-pg-qt)

enable_testing()

find_package(ECM 1.1.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(ECMAddTests)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)
include(WriteBasicConfigVersionFile)

set(CMAKECONFIG_INSTALL_DIR ${LIB_INSTALL_DIR}/cmake/KDevelop-PG-Qt)
ecm_configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/KDevelop-PG-QtConfig.cmake.in"
                                  "${CMAKE_CURRENT_BINARY_DIR}/KDevelop-PG-QtConfig.cmake"
                                  INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)
ecm_setup_version(${KDEVELOP_PG_QT_VERSION_MAJOR}.${KDEVELOP_PG_QT_VERSION_MINOR}.${KDEVELOP_PG_QT_VERSION_PATCH}
                  VARIABLE_PREFIX KDEVELOP_PG_QT
                  VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kdevelop-pg-qt_version.h"
                  PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KDevelop-PG-QtConfigVersion.cmake"
                  SOVERSION ${KDEVELOP_PG_QT_LIB_SOVERSION}
)
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/kdevelop-pg-qt_version.h"
        DESTINATION "${KDE_INSTALL_INCLUDEDIR}/kdevelop-pg-qt")
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KDevelop-PG-QtConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KDevelop-PG-QtConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}" )

set(REQUIRED_QT_VERSION 5.2.0)
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Core Test)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_program(FLEX_EXECUTABLE
  NAMES flex
  PATHS /usr/bin
  DOC "Flex executable")

find_program(BISON_EXECUTABLE
  NAMES bison
  PATHS /usr/bin
  DOC "bison executable")

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS -DQT_NO_URL_CAST_FROM_STRING)
add_definitions(-DQT_DEPRECATED_WARNINGS -DQT_DISABLE_DEPRECATED_BEFORE=0x050400)

# Silence a few warnings
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-field-initializers -Wno-unused-local-typedefs")
endif()

add_subdirectory(include)
add_subdirectory(kdev-pg)
add_subdirectory(examples EXCLUDE_FROM_ALL)
add_subdirectory(tests)

include(CTest)

# CTestCustom.cmake has to be in the CTEST_BINARY_DIR.
# in the KDE build system, this is the same as CMAKE_BINARY_DIR.
configure_file(${CMAKE_SOURCE_DIR}/CTestCustom.cmake ${CMAKE_BINARY_DIR}/CTestCustom.cmake)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
