include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

set(SOURCES
    storage_engine/Type.h

    main.cpp
)

add_executable(db07 ${SOURCES})
