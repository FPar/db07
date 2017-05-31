include_directories(
    ${CMAKE_SOURCE_DIR}/src/core
)

set(SOURCES
	main.cpp
)

add_executable(db07 ${SOURCES})
target_link_libraries(db07 db07_core)
