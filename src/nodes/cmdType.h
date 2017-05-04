#ifndef CMD_TYPE_H
#define CMD_TYPE_H

namespace db07 {
    enum class cmdType {
        query_select,
        dml_update,
        dml_insert,
        dml_delete,
        ddl_statement
    };
}

#endif // !CMD_TYPES_H
