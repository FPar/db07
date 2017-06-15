#ifndef CREATE_TABLE_COMMAND_H
#define CREATE_TABLE_COMMAND_H

#include <memory>
#include <storage_engine/Table_definition.h>
#include <storage_engine/Global_object_store.h>

namespace db07 {
    class Create_table_command {
    public:
        Create_table_command(const std::string &name, std::shared_ptr<Table_definition> &table_definition) :
                _name(name), _table_definition(std::move(table_definition)) {}

        void execute(Global_object_store &global_object_store);

    private:
        std::string _name;
        std::shared_ptr<Table_definition> _table_definition;
    };
}

#endif
