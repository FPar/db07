#ifndef CREATE_PRODUCTS_TABLE_H
#define CREATE_PRODUCTS_TABLE_H

#include <commands/Create_table_command.h>

class Create_products_table {
public:
    std::unique_ptr<db07::Create_table_command> command();
};


#endif
