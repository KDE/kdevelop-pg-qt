add_library(KDevPGQtUtils INTERFACE)
add_library(KDevelopPGQt::Utils ALIAS KDevPGQtUtils)

set_target_properties(KDevPGQtUtils PROPERTIES
    EXPORT_NAME "Utils"
)

target_include_directories(KDevPGQtUtils
    INTERFACE
        "$<INSTALL_INTERFACE:${KDEVELOP_PG_QT_INSTALL_INCLUDEDIR}>"
)

install(TARGETS KDevPGQtUtils EXPORT KDevelopPGQtTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install( FILES
    kdev-pg-allocator.h
    kdev-pg-location-table.h
    kdev-pg-memory-pool.h
    kdev-pg-token-stream.h
    kdev-pg-list.h
    kdev-pg-char-sets.h
    DESTINATION ${KDEVELOP_PG_QT_INSTALL_INCLUDEDIR}
)
