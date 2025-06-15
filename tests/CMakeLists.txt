# Включаем автоматическую генерацию MOC
set(CMAKE_AUTOMOC ON)

# Создаем тестовый исполняемый файл
add_executable(tests
    test_main.cpp
    test_mainwindow.cpp
    test_event.cpp
    ../mainwindow.cpp
    ../event.cpp
    ../pet.cpp
)

# Указываем правильные include-директории
target_include_directories(tests PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Qt6Test_INCLUDE_DIRS}
)

# Подключаем необходимые библиотеки Qt
target_link_libraries(tests PRIVATE
    Qt6::Test
    Qt6::Core
    Qt6::Widgets
)

# Добавляем тест в CTest
add_test(NAME tests COMMAND tests)