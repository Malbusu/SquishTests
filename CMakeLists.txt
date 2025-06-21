cmake_minimum_required(VERSION 3.16)

project(SquishTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets )

qt_standard_project_setup(REQUIRES 6.8)

qt_add_resources(RESOURCES qml.qrc)


qt_add_executable(appSquishTests
    main.cpp
    backend.cpp
    backend.h
    Task.h
    Task.cpp
    tasksmodel.h
    tasksmodel.cpp
    taskfilterproxymodel.h
    taskfilterproxymodel.cpp
)

target_sources(appSquishTests PRIVATE ${RESOURCES})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSquishTests PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSquishTests
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSquishTests
    PRIVATE
            Qt6::Core
            Qt6::Gui
            Qt6::Qml
            Qt6::Quick
            Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS appSquishTests
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
