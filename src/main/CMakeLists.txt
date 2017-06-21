include_directories(
    ${CMAKE_SOURCE_DIR}/src/core
)

set(SOURCES
    example/Create_tables.cpp
    example/Create_tables.h
    example/Insert_data.cpp
    example/Insert_data.h
    example/Select_sales.cpp
    example/Select_sales.h

    main.cpp)

add_executable(db07 ${SOURCES})
target_link_libraries(db07 db07_core)
