cmake_minimum_required(VERSION 3.16)

project(CplusPlusTaak VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# === paden naar jouw mappen ===
set(PRJ_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/ProjectFiles)

# === alle bronnen ===
set(PROJECT_SOURCES
    ${PRJ_DIR}/main.cpp
    ${PRJ_DIR}/mainwindow.cpp
    ${PRJ_DIR}/mainwindow.h
    ${PRJ_DIR}/mainwindow.ui

    ${PRJ_DIR}/gamemanager.cpp
    ${PRJ_DIR}/gamemanager.h

    ${PRJ_DIR}/characterclass.cpp
    ${PRJ_DIR}/characterclass.h

    ${PRJ_DIR}/playerclass.cpp
    ${PRJ_DIR}/playerclass.h

    ${PRJ_DIR}/Creatureclass.cpp
    ${PRJ_DIR}/Creatureclass.h

    ${PRJ_DIR}/creaturedatabase.cpp
    ${PRJ_DIR}/creaturedatabase.h

    ${PRJ_DIR}/battlescreen.cpp
    ${PRJ_DIR}/battlescreen.h
    ${PRJ_DIR}/battlescreen.ui

    ${PRJ_DIR}/choicescreen.cpp
    ${PRJ_DIR}/choicescreen.h
    ${PRJ_DIR}/choicescreen.ui

    ${PRJ_DIR}/partyscreen.cpp
    ${PRJ_DIR}/partyscreen.h
    ${PRJ_DIR}/partyscreen.ui

    ${PRJ_DIR}/storescreen.cpp
    ${PRJ_DIR}/storescreen.h
    ${PRJ_DIR}/storescreen.ui

    ${PRJ_DIR}/startscreen.cpp
    ${PRJ_DIR}/startscreen.h
    ${PRJ_DIR}/startscreen.ui

    ${PRJ_DIR}/move.h
    ${PRJ_DIR}/totalmovesclass.cpp
    ${PRJ_DIR}/totalmovesclass.h

    ${PRJ_DIR}/equipment.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CplusPlusTaak
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
        ProjectFiles/characterdebugger.h ProjectFiles/characterdebugger.cpp

    )
else()
    add_executable(CplusPlusTaak
        ${PROJECT_SOURCES}
    )
endif()

# include‑paden voor je headers
target_include_directories(CplusPlusTaak PRIVATE
    ${PRJ_DIR}

)


target_link_libraries(CplusPlusTaak PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CplusPlusTaak)
endif()
set_target_properties(CplusPlusTaak PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CplusPlusTaak
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CplusPlusTaak)
endif()
