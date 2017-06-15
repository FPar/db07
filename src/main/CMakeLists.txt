include_directories(
    ${CMAKE_SOURCE_DIR}/src/core
)

set(SOURCES
    example/Create_products_table.cpp
    example/Create_products_table.h
    example/Insert_product_data.cpp
    example/Insert_product_data.h
    example/Select_product_by_id.cpp
    example/Select_product_by_id.h

    main.cpp)

add_executable(db07 ${SOURCES})
target_link_libraries(db07 db07_core)
