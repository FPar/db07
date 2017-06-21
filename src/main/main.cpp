#include <string>
#include <iostream>
#include <storage_engine/Global_object_store.h>
#include <optimizer/Query_data.h>
#include <optimizer/Plan.h>
#include "example/Create_tables.h"
#include "example/Insert_data.h"
#include "example/Select_sales.h"

using namespace std;
using namespace db07;

string read_command();

bool terminates_command(string &line);

int main(int argc, char **argv) {
    Global_object_store object_store;

    {
        Create_tables create_tables;
        unique_ptr<Create_table_command> c = create_tables.product();
        c->execute(object_store);
        c = create_tables.sales();
        c->execute(object_store);

        Insert_data insert_data;
        unique_ptr<Insert_plan> i = insert_data.product(object_store);
        i->execute();
        i = insert_data.sales(object_store);
        i->execute();

        Select_sales select_sales;
        unique_ptr<Select_plan> s = select_sales.plan(object_store);
        s->execute();
    }

    string command;
    while ((command = read_command()) != "exit;") {
        // TODO: Get query data from parser.
        Query_data *query;
        // TODO: Get plan from query data.
        Plan *plan;
        plan->execute();
    }

    return 0;
}

string read_command() {
    string command;
    string line;

    cout << "db07 > " << flush;
    do {
        cin >> line;
        command.append(line);
    } while (!terminates_command(line));

    return command;
}

bool terminates_command(string &line) {
    for (auto i = line.crbegin(); i != line.crend(); ++i) {
        switch (*i) {
            case ' ':
                break;
            case ';':
                return true;
            default:
                return false;
        }
    }
    return false;
}
