include_directories(
    ${CMAKE_SOURCE_DIR}/vendor/catch
    ${CMAKE_SOURCE_DIR}/src
)

set(TEST_SOURCES
    main.cpp
)

add_executable(db07_test ${TEST_SOURCES})

enable_testing()
add_test(db07_test db07_test)
