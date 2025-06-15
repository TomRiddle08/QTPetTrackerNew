set(CMAKE_AUTOMOC ON)

add_executable(tests
    test_main.cpp  # Только этот файл
    ${CMAKE_SOURCE_DIR}/event.cpp
    ${CMAKE_SOURCE_DIR}/pet.cpp
)

target_include_directories(tests PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${Qt6Test_INCLUDE_DIRS}
)

target_link_libraries(tests PRIVATE
    Qt6::Test
    Qt6::Core
)

add_test(NAME tests COMMAND tests)