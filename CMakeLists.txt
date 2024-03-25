cmake_minimum_required(VERSION 3.16)

project(kdevelop-pg-qt VERSION 2.2.90)

find_package(ECM 6.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

set(KDE_COMPILERSETTINGS_LEVEL 5.84)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(ECMAddTests)
include(ECMMarkNonGuiExecutable)
include(ECMSetupVersion)
include(ECMDeprecationSettings)

include(FeatureSummary)
include(WriteBasicConfigVersionFile)
include(CMakePackageConfigHelpers)

set(CMAKECONFIG_INSTALL_DIR ${KDE_INSTALL_CMAKEPACKAGEDIR}/KDevelop-PG-Qt)
configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/KDevelop-PG-QtConfig.cmake.in"
                              "${CMAKE_CURRENT_BINARY_DIR}/KDevelop-PG-QtConfig.cmake"
                              INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)
ecm_setup_version(${kdevelop-pg-qt_VERSION_MAJOR}.${kdevelop-pg-qt_VERSION_MINOR}.${kdevelop-pg-qt_VERSION_PATCH}
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

if(BUILD_TESTING)
  set(REQUIRED_QT_TESTCOMPONENTS Test)
endif()

set(REQUIRED_QT_VERSION "6.5.0")
find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED
  COMPONENTS
    Core
    ${REQUIRED_QT_TESTCOMPONENTS}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_program(FLEX_EXECUTABLE
  NAMES flex
  PATHS /usr/bin
  DOC "Flex executable")

find_program(BISON_EXECUTABLE
  NAMES bison
  PATHS /usr/bin
  DOC "bison executable")

ecm_set_disabled_deprecation_versions(
    QT 5.15.2
)

add_definitions(
    -DQT_NO_SIGNALS_SLOTS_KEYWORDS
    -DQT_STRICT_ITERATORS
    -DQT_USE_QSTRINGBUILDER
    -DQT_NO_URL_CAST_FROM_STRING
    -DQT_NO_CAST_FROM_BYTEARRAY
    -DQT_NO_CAST_TO_ASCII
)

# Silence a few warnings
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-field-initializers -Wno-unused-local-typedefs")
endif()

add_subdirectory(include)
add_subdirectory(kdev-pg)
add_subdirectory(examples EXCLUDE_FROM_ALL)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
