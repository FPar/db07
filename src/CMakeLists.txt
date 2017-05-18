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
	optimizer/Select_plan.cpp
    optimizer/Select_plan.h

    parser/Lexer.cpp
    parser/Lexer.h
    parser/Token.cpp
    parser/Token.h
    parser/Token_evaluator.h
    parser/Token_recognizer.cpp
    parser/Token_recognizer.h
    parser/token_type.h
	
	plan/matching/Condition.h
	plan/Relation_scan.cpp
	plan/Relation_scan.h

    storage_engine/Attribute.h
    storage_engine/Bitmap.cpp
    storage_engine/Bitmap.h
	storage_engine/Btree.cpp
	storage_engine/Btree.h
	storage_engine/Global_catalog.h
	storage_engine/Catalog.h
	storage_engine/Catalog_item.h
	storage_engine/catalog_item_exists.h
	storage_engine/catalog_item_not_found.h
	storage_engine/Relation.h
	storage_engine/Tuple.cpp
	storage_engine/Tuple.h
	storage_engine/Tuple_data.cpp
	storage_engine/Tuple_data.h
    storage_engine/Type.h

	storage_engine/types/Tuple_value.h

    main.cpp
)

add_library(db07_core ${SOURCES})
add_executable(db07 ${SOURCES})
