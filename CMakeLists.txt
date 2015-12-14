cmake_minimum_required(VERSION 2.8.12)
project(kdevelop-pg-qt)

enable_testing()

set(REQUIRED_QT_VERSION 5.2.0)
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Core Test)

find_package(ECM 1.1.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(ECMAddTests)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

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

add_subdirectory(cmake)
add_subdirectory(include)
add_subdirectory(kdev-pg)
add_subdirectory(examples EXCLUDE_FROM_ALL)
add_subdirectory(tests)

include(CTest)

# CTestCustom.cmake has to be in the CTEST_BINARY_DIR.
# in the KDE build system, this is the same as CMAKE_BINARY_DIR.
configure_file(${CMAKE_SOURCE_DIR}/CTestCustom.cmake ${CMAKE_BINARY_DIR}/CTestCustom.cmake)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
