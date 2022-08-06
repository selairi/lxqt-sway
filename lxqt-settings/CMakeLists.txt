set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(USE_QT6 "Force use the Qt6." $ENV{USE_QT6})
option(USE_QT5 "Force use the Qt5." $ENV{USE_QT5})

if((USE_QT6 AND USE_QT5) OR
   (NOT USE_QT6 AND NOT USE_QT5))

    # Autodetect Qt version
    find_package(Qt5 QUIET)
    message("-- Searching for Qt6")
    if(DEFINED Qt5_FOUND)
        set(USE_QT5 ON)
        set(USE_QT6 OFF)
        message("-- Qt5 ${USE_QT5}")
    else()
        set(USE_QT5 OFF)
        set(USE_QT6 ON)
        message("-- Qt6 ${USE_QT6}")
    endif()
endif()

if(USE_QT5)
    find_package(Qt5 COMPONENTS Core REQUIRED)
else()
    find_package(Qt6 COMPONENTS Core REQUIRED)
endif()

add_executable(lxqt-settings
    main.cpp
)


set(SHARE_FILES

)

set(APP_ICON_FILES

)

# Config file
#configure_file ( config.in config.h )
#configure_file ( desktop_files/ssh_helper.desktop.in ssh_helper.desktop )

target_include_directories(lxqt-settings PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_BINARY_DIR}"
  "${PROJECT_BINARY_DIR}"
#  "${PROJECT_SOURCE_DIR}/configfileparser"
)

if(USE_QT5)
  target_link_libraries(lxqt-settings
    PRIVATE Qt5::Core
  )
else()
  target_link_libraries(lxqt-settings
    PRIVATE Qt6::Core
  )
endif()


install(TARGETS lxqt-settings RUNTIME DESTINATION bin)
#install(FILES ${SHARE_FILES} DESTINATION share/ssh_helper)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ssh_helper.desktop DESTINATION share/applications)
#install(FILES ${APP_ICON_FILES} DESTINATION share/icons/hicolor/scalable/apps)


