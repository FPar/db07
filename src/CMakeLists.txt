include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

set(SOURCES
    control/Destination_receiver.h

    executor/Executor.h
    executor/Executor.cpp
    
    nodes/cmdType.h

    optimizer/Query_plan.h

    storage_engine/Type.h

    main.cpp
)

add_executable(db07 ${SOURCES})
