cmake_minimum_required(VERSION 3.16)

project(kdevelop-pg-qt VERSION 2.3.90)

find_package(ECM 6.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

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

option(BUILD_EXAMPLES "Build examples" OFF)

if(BUILD_TESTING)
  set(REQUIRED_QT_TESTCOMPONENTS Test)
endif()

set(REQUIRED_QT_VERSION "6.5.0")
find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED
  COMPONENTS
    Core
    ${REQUIRED_QT_TESTCOMPONENTS}
)

find_package(FLEX)
set_package_properties(FLEX PROPERTIES
    TYPE RECOMMENDED
)

find_package(BISON)
set_package_properties(BISON PROPERTIES
    TYPE RECOMMENDED
)

ecm_set_disabled_deprecation_versions(
    QT 5.15.2
)

# added by KDE_COMPILERSETTINGS_LEVEL 5.85.0
remove_definitions(
    -DQT_NO_CAST_FROM_ASCII
)

# Silence a few warnings
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-field-initializers -Wno-unused-local-typedefs")
endif()

add_subdirectory(src)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
