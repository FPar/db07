include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

set(SOURCES
    control/Destination_receiver.cpp
    control/Destination_receiver.h

    executor/Executor.h
    executor/Executor.cpp
    
    nodes/cmdType.h

    optimizer/Query_plan.h

    parser/lexer.cpp
    parser/lexer.h
    parser/token_type.h
    parser/token.h
    parser/token.cpp
    parser/token_evaluator.h
    parser/token_recognizer.cpp
    parser/token_recognizer.h

    storage_engine/Attribute.h
    storage_engine/Type.h

    main.cpp
)

add_library(db07_core ${SOURCES})
add_executable(db07 ${SOURCES})
