cmake_minimum_required(VERSION 3.16)

project(kursovaya11 VERSION 0.1 LANGUAGES CXX)

# Настройки для покрытия кода
option(ENABLE_COVERAGE "Enable coverage reporting" ON)
if(ENABLE_COVERAGE)
    add_compile_options(--coverage -fprofile-arcs -ftest-coverage)
    add_link_options(--coverage)
endif()

# Включаем автоматическую обработку .ui, .qrc, MOC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем Qt5 или Qt6 с компонентами Widgets и Test
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Test)

# Определяем исходные файлы проекта
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    event.h
    event.cpp
    add_event_dialog.h
    add_event_dialog.cpp
    pet.h
    pet.cpp
    edit_pet_dialog.h
    edit_pet_dialog.cpp
    resources.qrc
    styles.qss
)

# Создаём исполняемый файл
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(kursovaya11
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(kursovaya11 SHARED ${PROJECT_SOURCES})
    else()
        add_executable(kursovaya11 ${PROJECT_SOURCES})
    endif()
endif()

# Подключаем библиотеки
target_link_libraries(kursovaya11 PRIVATE 
    Qt::Widgets
)

# Настройки для macOS
if(${QT_VERSION_MAJOR} EQUAL 5 OR (${QT_VERSION_MAJOR} EQUAL 6 AND QT_VERSION_MINOR LESS 1))
    set_target_properties(kursovaya11 PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER com.example.kursovaya11
    )
endif()

set_target_properties(kursovaya11 PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Включаем тестирование
enable_testing()

# Добавляем поддиректорию с тестами
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)
    add_subdirectory(tests)
endif()

# Установка (для дистрибуции)
include(GNUInstallDirs)
install(TARGETS kursovaya11
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Генерация файла compile_commands.json для анализа кода
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)