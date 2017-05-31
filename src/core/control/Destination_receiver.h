#ifndef DESTINATION_RECEIVER_H
#define DESTINATION_RECEIVER_H

#include "storage_engine/Column.h"
#include "storage_engine/Row.h"

namespace db07 {
    class Destination_receiver {
    private:
        Table_definition *m_description;

        void horizontal_line();

    public:
        Destination_receiver(Table_definition *description);
        ~Destination_receiver();

        void receive(Row &tuple);
    };
}

#endif // !EXECUTOR_DESTINATION_H
