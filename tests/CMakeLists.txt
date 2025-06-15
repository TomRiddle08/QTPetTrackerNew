add_executable(tests
    test_main.cpp
    ${CMAKE_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_SOURCE_DIR}/event.cpp
    ${CMAKE_SOURCE_DIR}/pet.cpp
)
target_link_libraries(tests PRIVATE Qt::Test)
add_test(NAME tests COMMAND tests)