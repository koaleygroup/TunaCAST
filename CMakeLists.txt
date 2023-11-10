cmake_minimum_required(VERSION 3.16)

project(TunaCastApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.6 REQUIRED COMPONENTS Quick Gui Multimedia MultimediaWidgets Widgets)

qt_standard_project_setup()

qt_add_executable(appTunaCastApp
    src/cpp/main.cpp
    src/cpp/screencapturepreview.cpp
    src/cpp/screencapturepreview.h
    src/cpp/screenlistmodel.h
    src/cpp/screenlistmodel.cpp
    src/cpp/windowlistmodel.h
    src/cpp/windowlistmodel.cpp
)

qt_add_qml_module(appTunaCastApp
    URI TunaCastApp
    VERSION 1.0
    RESOURCES
        src/assets/logo.jpg
        src/assets/busy.gif
    QML_FILES
        src/qml/Main.qml
        src/qml/views/CastWindow.qml
        src/qml/views/AvailableDevices.qml
        src/qml/views/Splash.qml
    QML_FILES src/qml/controls/BusyWidget.qml
    SOURCES src/cpp/qmlinterface.h src/cpp/qmlinterface.cpp
    QML_FILES src/qml/controls/AvailableScreensDelegate.qml
    QML_FILES src/qml/controls/AvailableWindowsDelegate.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appTunaCastApp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appTunaCastApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTunaCastApp
    PRIVATE Qt6::Quick Qt6::Gui Qt6::Multimedia Qt6::Widgets Qt6::MultimediaWidgets
)

include(GNUInstallDirs)
install(TARGETS appTunaCastApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
