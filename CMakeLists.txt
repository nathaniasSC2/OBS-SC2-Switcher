cmake_minimum_required(VERSION 3.16)

project(obs-sc2-switcher VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OBS dependencies
find_package(libobs REQUIRED)
find_package(obs-frontend-api REQUIRED)

# Find Qt6 dependencies
find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

# Find external dependencies
find_package(CURL REQUIRED)

# Jansson is typically bundled with OBS or provided as a dependency.
# On modern systems, we can check for it.
find_package(PkgConfig)
if(PkgConfig_FOUND)
    pkg_check_modules(JANSSON jansson)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(sc2switcher_HEADERS
    APIState.h
    Config.h
    Constants.h
    log.h
    obs-util.h
    Observer.h
    SC2Data.h
    SC2State.h
    SceneSwitcher.h
    ScoreTracker.h
    Webhook.h
    forms/SettingsDialog.h
)

set(sc2switcher_SOURCES
    sc2switcher.cpp
    SC2Data.cpp
    SC2State.cpp
    SceneSwitcher.cpp
    ScoreTracker.cpp
    Webhook.cpp
    Config.cpp
    forms/SettingsDialog.cpp
)

set(sc2switcher_UI
    forms/SettingsDialog.ui
)

add_library(obs-sc2-switcher MODULE
    ${sc2switcher_HEADERS}
    ${sc2switcher_SOURCES}
    ${sc2switcher_UI}
)

target_link_libraries(obs-sc2-switcher
    PRIVATE
    OBS::libobs
    OBS::obs-frontend-api
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    CURL::libcurl
)

target_include_directories(obs-sc2-switcher PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(JANSSON_LIBRARIES)
    target_link_libraries(obs-sc2-switcher PRIVATE ${JANSSON_LIBRARIES})
    target_include_directories(obs-sc2-switcher PRIVATE ${JANSSON_INCLUDE_DIRS})
elseif(JANSSON_FOUND)
    target_link_libraries(obs-sc2-switcher PRIVATE ${JANSSON_LIBRARIES})
    target_include_directories(obs-sc2-switcher PRIVATE ${JANSSON_INCLUDE_DIRS})
else()
    # Assume it's in standard paths or provided by libobs
    target_link_libraries(obs-sc2-switcher PRIVATE jansson)
endif()

# Installation logic
if(WIN32)
    set(PLUGIN_INSTALL_DIR "bin/64bit")
else()
    set(PLUGIN_INSTALL_DIR "lib/obs-plugins")
endif()

install(TARGETS obs-sc2-switcher
    LIBRARY DESTINATION ${PLUGIN_INSTALL_DIR}
    RUNTIME DESTINATION ${PLUGIN_INSTALL_DIR}
)
