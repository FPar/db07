#ifndef DESTINATION_RECEIVER_H
#define DESTINATION_RECEIVER_H

#include <memory>
#include <storage_engine/Table_definition.h>
#include <storage_engine/Row.h>

namespace db07 {
    class Destination_receiver {
    private:
        const std::shared_ptr<Table_definition> _description;

        void horizontal_line();

    public:
        Destination_receiver(const std::shared_ptr<Table_definition> &description);

        ~Destination_receiver();

        void receive(Row &row);
    };
}

#endif
