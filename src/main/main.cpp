#include <string>
#include <iostream>
#include "storage_engine/Global_object_store.h"
#include "optimizer/Query_data.h"
#include "optimizer/Plan.h"

using namespace std;
using namespace db07;

string read_command();

bool terminates_command(string &line);

int main(int argc, char **argv) {
    Global_object_store object_store;

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
