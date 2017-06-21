include_directories(
    ${CMAKE_SOURCE_DIR}/src/core
)

set(SOURCES
    commands/Create_table_command.cpp
    commands/Create_table_command.h

    control/Destination_receiver.cpp
    control/Destination_receiver.h

    optimizer/Insert_plan.cpp
    optimizer/Insert_plan.h
    optimizer/Plan.h
    optimizer/Query_condition.cpp
    optimizer/Query_condition.h
    optimizer/Query_data.cpp
    optimizer/Query_data.h
    optimizer/Select_plan.cpp
    optimizer/Select_plan.h
    optimizer/Query_type.h
    optimizer/Build_Plan.cpp
    optimizer/Build_Plan.h

    parser/Lexer.cpp
    parser/Lexer.h
    parser/Token.cpp
    parser/Token.h
    parser/Token_evaluator.cpp
    parser/Token_evaluator.h
    parser/Token_recognizer.cpp
    parser/Token_recognizer.h
    parser/token_type.h
    parser/Parser.cpp
    parser/Parser.h
    parser/Recognition_rule.h
    parser/Recognition_rule.cpp
    parser/String_recognition_rule.cpp
    parser/String_recognition_rule.h
    parser/Regex_recognition_rule.cpp
    parser/Regex_recognition_rule.h

    plan/matching/And_condition.cpp
    plan/matching/And_condition.h
    plan/matching/Comparing_condition.cpp
    plan/matching/Comparing_condition.h
    plan/matching/Condition.h
    plan/matching/Equals_condition.cpp
    plan/matching/Equals_condition.h
    plan/matching/Greater_condition.cpp
    plan/matching/Greater_condition.h
    plan/matching/Greater_equals_condition.cpp
    plan/matching/Greater_equals_condition.h
    plan/matching/Less_condition.cpp
    plan/matching/Less_condition.h
    plan/matching/Less_equals_condition.cpp
    plan/matching/Less_equals_condition.h
    plan/matching/Or_condition.cpp
    plan/matching/Or_condition.h
    plan/matching/Unequals_condition.cpp
    plan/matching/Unequals_condition.h

    plan/Hash_match.cpp
    plan/Hash_match.h
    plan/Insert_data_node.cpp
    plan/Insert_data_node.h
    plan/Plan_node.h
    plan/Projection.cpp
    plan/Projection.h
    plan/Table_scan.cpp
    plan/Table_scan.h

    storage_engine/types/Type.h
    storage_engine/types/Types.cpp
    storage_engine/types/Types.h

    storage_engine/values/Int_value.cpp
    storage_engine/values/Int_value.h
    storage_engine/values/Value.h
    storage_engine/values/values.h
    storage_engine/values/Varchar_value.cpp
    storage_engine/values/Varchar_value.h

    storage_engine/Btree.cpp
    storage_engine/Btree.h
    storage_engine/Column.h
    storage_engine/Global_object_store.cpp
    storage_engine/Global_object_store.h
    storage_engine/Object_store.h
    storage_engine/Object_store_item.h
    storage_engine/object_store_item_exists.h
    storage_engine/object_store_item_not_found.h
    storage_engine/Row.cpp
    storage_engine/Row.h
    storage_engine/Table.cpp
    storage_engine/Table.h
    storage_engine/Table_definition.cpp
    storage_engine/Table_definition.h
    storage_engine/Table_definition_builder.cpp
    storage_engine/Table_definition_builder.h)

add_library(db07_core ${SOURCES})
