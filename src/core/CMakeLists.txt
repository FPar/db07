include_directories(
    ${CMAKE_SOURCE_DIR}/src/core
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
	
	plan/matching/And_condition.cpp
	plan/matching/And_condition.h
	plan/matching/Condition.h
	plan/matching/Equals_condition.cpp
	plan/matching/Equals_condition.h
	plan/matching/Or_condition.cpp
	plan/matching/Or_condition.h

	plan/Relation_scan.cpp
	plan/Relation_scan.h

	storage_engine/types/Type.h
    storage_engine/types/Types.cpp
    storage_engine/types/Types.h

	storage_engine/values/Value.h
    storage_engine/values/Int_value.cpp
    storage_engine/values/Int_value.h

    storage_engine/Bitmap.cpp
    storage_engine/Bitmap.h
	storage_engine/Btree.cpp
	storage_engine/Btree.h
    storage_engine/Column.h
	storage_engine/Global_object_store.h
	storage_engine/Object_store.h
	storage_engine/Object_store_item.h
	storage_engine/object_store_item_exists.h
	storage_engine/object_store_item_not_found.h
	storage_engine/Row.cpp
	storage_engine/Row.h
	storage_engine/Table.h
)

add_library(db07_core ${SOURCES})
