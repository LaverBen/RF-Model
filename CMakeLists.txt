cmake_minimum_required(VERSION 3.16)

project(RF-Model VERSION 0.1 LANGUAGES CXX)

option(RFMODEL_BUILD_TESTS "Build RF-Model test suite" ON)
option(RFMODEL_BUILD_BENCH "Build RF-Model benchmarks" OFF)

include(GNUInstallDirs)
include(CTest)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(APP_SOURCES
        app/logging.cpp
        app/main.cpp
        app/mainwindow.cpp
        app/mainwindow.h
        app/logging.h
)

set(UI_FORMS
        ui/mainwindow.ui
)

set(PROJECT_SOURCES
        ${APP_SOURCES}
        ${UI_FORMS}
)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

add_library(rfmodel_engine INTERFACE)
target_include_directories(rfmodel_engine INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/engine/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_library(rfmodel_math INTERFACE)
target_include_directories(rfmodel_math INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/math/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RF-Model
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET RF-Model APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(RF-Model SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(RF-Model
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(RF-Model PRIVATE Qt${QT_VERSION_MAJOR}::Widgets rfmodel_engine rfmodel_math)
target_include_directories(RF-Model PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/app
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.RF-Model)
endif()
set_target_properties(RF-Model PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS rfmodel_engine rfmodel_math
    EXPORT rfmodelTargets
)

install(TARGETS RF-Model
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY engine/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY math/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT rfmodelTargets
    NAMESPACE rfmodel::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/RF-Model
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RF-Model)
endif()

if(RFMODEL_BUILD_TESTS)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
        add_subdirectory(tests)
    endif()
endif()

if(RFMODEL_BUILD_BENCH)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/bench/CMakeLists.txt")
        add_subdirectory(bench)
    endif()
endif()
