find_package(lxqt ${LXQT_MINIMUM_VERSION} REQUIRED)

include(GNUInstallDirs)
include(LXQtConfigVars)

# startlxqtsway script
set(PREDEF_XDG_DATA_DIRS "$XDG_DATA_HOME")
if(NOT("${LXQT_DATA_DIR}" MATCHES "^/usr(/local)?/share$"))
    set(PREDEF_XDG_DATA_DIRS "${PREDEF_XDG_DATA_DIRS}:${LXQT_DATA_DIR}")
endif()
set(PREDEF_XDG_DATA_DIRS "${PREDEF_XDG_DATA_DIRS}:/usr/local/share:/usr/share")
set(PREDEF_XDG_CONFIG_DIRS "/etc:${LXQT_ETC_XDG_DIR}:/usr/share")
configure_file(startlxqtsway.in startlxqtsway @ONLY)
install(PROGRAMS
    "${CMAKE_CURRENT_BINARY_DIR}/startlxqtsway"
    DESTINATION bin
    COMPONENT Runtime
)

install(PROGRAMS
    lxqt-sway-get-config.sh
    DESTINATION bin
    COMPONENT Runtime
)
