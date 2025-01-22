cmake_minimum_required(VERSION 3.21)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/.cmake/)

project(sast-gallery VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)

file(GLOB_RECURSE PROJECT_SOURCES
    src/*.cpp
    src/*.h
    3rdpart/ElaWidgetTools/src/DeveloperComponents/*.cpp
)

qt_add_executable(sast-gallery
    ${PROJECT_SOURCES}
    3rdpart/ElaWidgetTools/src/include/ElaWidgetTools.qrc
    res/res.qrc
    res/icon/app.rc
)

# Add ElaWidgetTools
add_subdirectory(3rdpart/ElaWidgetTools)

target_include_directories(sast-gallery PRIVATE
    src
    3rdpart/ElaWidgetTools/src/include
)

target_link_libraries(sast-gallery PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
    ElaWidgetTools
)

# copy ElaWidgetTools library to compile output dir, useful for vscode
if(win32)
    add_custom_command(TARGET sast-gallery POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:sast-gallery> $<TARGET_FILE:ElaWidgetTools>
        COMMAND_EXPAND_LISTS
    )
endif()

if(win32)
  configure_file(
      ${CMAKE_SOURCE_DIR}/.cmake/InstallerScript.iss.in
      ${CMAKE_SOURCE_DIR}/action-cli/InstallerScript.iss
  )
endif()

if(APPLE)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER ${IDENTIFIER})
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(MACOSX_BUNDLE_COPYRIGHT ${COPYRIGHT})

    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${spectral_VERSION})
    set(MACOSX_BUNDLE_BUNDLE_VERSION ${spectral_VERSION})

    set(ICON_NAME "res/icon/app.icns")
    set(${PROJECT_NAME}_MAC_ICON "${CMAKE_SOURCE_DIR}/${ICON_NAME}")
    set(MACOSX_BUNDLE_ICON_FILE ${ICON_NAME})
    set_property(SOURCE "${${PROJECT_NAME}_MAC_ICON}" PROPERTY
        MACOSX_PACKAGE_LOCATION Resources)
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.sast-gallery)
endif()
set_target_properties(sast-gallery PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS sast-gallery
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
