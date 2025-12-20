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
set(SRC_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/SourceFiles)
set(HDR_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/HeaderFiles)

# === alle bronnen ===
set(PROJECT_SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/mainwindow.cpp
    ${HDR_DIR}/mainwindow.h
    ${SRC_DIR}/mainwindow.ui

    ${SRC_DIR}/gamemanager.cpp
    ${HDR_DIR}/gamemanager.h

    ${SRC_DIR}/characterclass.cpp
    ${HDR_DIR}/characterclass.h

    ${SRC_DIR}/playerclass.cpp
    ${HDR_DIR}/playerclass.h

    ${SRC_DIR}/Creatureclass.cpp
    ${HDR_DIR}/Creatureclass.h

    ${SRC_DIR}/creaturedatabase.cpp
    ${HDR_DIR}/creaturedatabase.h

    ${SRC_DIR}/battlescreen.cpp
    ${HDR_DIR}/battlescreen.h
    ${SRC_DIR}/battlescreen.ui

    ${SRC_DIR}/choicescreen.cpp
    ${HDR_DIR}/choicescreen.h
    ${SRC_DIR}/choicescreen.ui

    ${SRC_DIR}/partyscreen.cpp
    ${HDR_DIR}/partyscreen.h
    ${SRC_DIR}/partyscreen.ui

    ${SRC_DIR}/storescreen.cpp
    ${HDR_DIR}/storescreen.h
    ${SRC_DIR}/storescreen.ui

    ${HDR_DIR}/move.h
    ${SRC_DIR}/totalmovesclass.cpp
    ${HDR_DIR}/totalmovesclass.h

    ${HDR_DIR}/equipment.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CplusPlusTaak
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(CplusPlusTaak
        ${PROJECT_SOURCES}
    )
endif()

# include‑paden voor je headers
target_include_directories(CplusPlusTaak PRIVATE
    ${HDR_DIR}
    ${SRC_DIR}
    ${FORMS_DIR}
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
