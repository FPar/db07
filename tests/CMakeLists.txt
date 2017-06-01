include_directories(
    ${CMAKE_SOURCE_DIR}/vendor/catch
    ${CMAKE_SOURCE_DIR}/src/core
)

set(TEST_SOURCES
    main.cpp
        parser/Token_test.cpp parser/Token_evaluator_test.cpp parser/Parser_test.cpp)

add_executable(db07_test ${TEST_SOURCES})

enable_testing()
add_test(db07_test db07_test)
target_link_libraries(db07_test db07_core)
