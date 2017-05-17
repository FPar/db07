include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

set(SOURCES
    control/Destination_receiver.cpp
    control/Destination_receiver.h

	optimizer/Plan.h
	optimizer/Plan_node.h
    optimizer/Query_condition.cpp
    optimizer/Query_condition.h
    optimizer/Query_data.cpp
    optimizer/Query_data.h
    optimizer/Select_plan.h

    parser/lexer.cpp
    parser/lexer.h
    parser/token_type.h
    parser/token.h
    parser/token.cpp
    parser/token_evaluator.h
    parser/token_recognizer.cpp
    parser/token_recognizer.h

    storage_engine/Attribute.h
	storage_engine/Global_catalog.h
	storage_engine/Catalog.h
	storage_engine/Catalog_item.h
	storage_engine/catalog_item_exists.h
	storage_engine/catalog_item_not_found.h
	storage_engine/Relation.h
    storage_engine/Type.h

    main.cpp
)

add_library(db07_core ${SOURCES})
add_executable(db07 ${SOURCES})
