cmake_minimum_required(VERSION 3.15)
project(qtermwidget)

if(Launcher_QT_VERSION_MAJOR EQUAL 6)
    set(QT_VERSION_MAJOR 6)
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network Multimedia)
endif()

set(QTERMWIDGET_SOURCES
    lib/utf8proc/utf8proc.c
    lib/util/CharWidth.cpp
    lib/util/ColorScheme.cpp
    lib/util/Filter.cpp
    lib/util/History.cpp
    lib/util/HistorySearch.cpp
    lib/util/KeyboardTranslator.cpp
    lib/util/SearchBar.cpp
    lib/util/TerminalCharacterDecoder.cpp
    lib/Emulation.cpp
    lib/Vt102Emulation.cpp
    lib/Screen.cpp
    lib/ScreenWindow.cpp
    lib/TerminalDisplay.cpp
    lib/qtermwidget.cpp
    lib/ptyqt/ptyqt.cpp
)

set(QTERMWIDGET_HEADERS
    lib/utf8proc/utf8proc.h
    lib/util/CharWidth.h
    lib/util/CharacterColor.h
    lib/util/Character.h
    lib/util/ColorScheme.h
    lib/util/Filter.h
    lib/util/History.h
    lib/util/HistorySearch.h
    lib/util/KeyboardTranslator.h
    lib/util/SearchBar.h
    lib/util/TerminalCharacterDecoder.h
    lib/Emulation.h
    lib/Vt102Emulation.h
    lib/Screen.h
    lib/ScreenWindow.h
    lib/TerminalDisplay.h
    lib/qtermwidget.h
    lib/qtermwidget_version.h
    lib/ptyqt/iptyprocess.h
    lib/ptyqt/ptyqt.h
)

set(QTERMWIDGET_FORMS
    lib/util/SearchBar.ui
)

set(QTERMWIDGET_RESOURCES
    lib/res.qrc
)

if(WIN32)
    list(APPEND QTERMWIDGET_SOURCES
        lib/ptyqt/conptyprocess.cpp
    )
    list(APPEND QTERMWIDGET_HEADERS
        lib/ptyqt/conptyprocess.h
    )
elseif(UNIX)
    list(APPEND QTERMWIDGET_SOURCES
        lib/ptyqt/unixptyprocess.cpp
    )
    list(APPEND QTERMWIDGET_HEADERS
        lib/ptyqt/unixptyprocess.h
    )
endif()

add_library(qtermwidget STATIC
    ${QTERMWIDGET_SOURCES}
    ${QTERMWIDGET_HEADERS}
    ${QTERMWIDGET_FORMS}
    ${QTERMWIDGET_RESOURCES}
)

set_target_properties(qtermwidget PROPERTIES AUTOUIC ON)

target_include_directories(qtermwidget PUBLIC
    lib
    lib/util
    lib/utf8proc
    lib/ptyqt
)

target_link_libraries(qtermwidget PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Multimedia
)

if(WIN32)
    target_link_libraries(qtermwidget PRIVATE
        Advapi32
        Crypt32
        Iphlpapi
        Netapi32
        Psapi
        Userenv
        Version
        Winmm
        Ws2_32
    )
elseif(UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(qtermwidget PRIVATE Threads::Threads ${CMAKE_DL_LIBS})
endif()
