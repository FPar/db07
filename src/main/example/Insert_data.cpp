#include <plan/Insert_data_node.h>
#include <storage_engine/Global_object_store.h>
#include <storage_engine/values/values.h>
#include "Insert_data.h"

using namespace std;
using namespace db07;

static vector<string> product_name = {"Pure Soft Detergent - 100ml", "Pure Soft Detergent - 200ml",
                                      "Pure Soft Detergent - 250ml", "Pure Soft Detergent - 500ml",
                                      "Detafast Stain Remover - 100ml", "Detafast Stain Remover - 200ml",
                                      "Detafast Stain Remover - 800ml", "Super Soft - Product Sample",
                                      "Super Soft - 250ml", "Super Soft - 500ml", "Super Soft - 1 Litre",
                                      "Super Soft Bulk - 2 Litres"};

static vector<double> product_price = {1.50, 2.00, 2.30, 3.50, 3.00, 3.50, 6.00, 0.30, 2.50, 3.50, 5.00, 8.00};

static vector<int> sales_cust_id = {23262, 23263, 23264, 23265, 23266, 23267, 23268, 23269, 23270, 23271, 23272, 23273,
                                    23274, 23275, 23276, 23277, 23278, 23279, 23280, 23281, 23282, 23283, 23284, 23285,
                                    23286, 23287, 23288, 23289, 23290, 23291, 23292, 23293, 23294, 23295, 23296, 23297,
                                    23298, 23299, 23300, 23301, 23302, 23303, 23304, 23305, 23306, 23307, 23308, 23309,
                                    23310, 23311, 23312, 23313, 23314, 23315, 23316, 23317, 23318, 23319, 23320, 23321,
                                    23322, 23323, 23324, 23325, 23326, 23327, 23328, 23329, 23330, 23331, 23332, 23333,
                                    23334, 23335, 23336, 23337, 23338, 23339, 23340, 23341, 23342, 23343, 23344, 23345,
                                    23346, 23347, 23348, 23349, 23350, 23351, 23352, 23353, 23354, 23355, 23356, 23357,
                                    23358, 23359, 23360, 23361};

static vector<string> sales_cust_name = {"Candice Levy", "Xerxes Smith", "Levi Douglas", "Uriel Benton", "Celeste Pugh",
                                         "Vance Campos", "Latifah Wall", "Jane Hernandez", "Wanda Garza",
                                         "Athena Fitzpatrick", "Anjolie Hicks", "Isaac Cooper", "Asher Weber",
                                         "Ethan Gregory", "Hayes Rollins", "MacKenzie Moss", "Aphrodite Brennan",
                                         "Angela Wise", "James Spencer", "Adria Kaufman", "Amir Alexander",
                                         "Lani Sweet", "Clark Weaver", "Leonard Cardenas", "Renee Padilla",
                                         "Joy Vazquez", "Ingrid Bush", "Deacon Craig", "Rama Goodwin",
                                         "Jelani Odonnell", "Liberty Mcbride", "Britanni Bender", "Samuel Ayala",
                                         "Shad Delacruz", "India Gilbert", "Ursula Mcconnell", "Ryder Conner",
                                         "Germaine Kidd", "Rhona Clarke", "Maxwell Parker", "Isaac Wolf",
                                         "Guinevere Key", "Deanna Santana", "Jared Sandoval", "Ima Cummings",
                                         "Oprah Ellis", "Dara Cunningham", "Buckminster Hopkins", "Kenyon Joyce",
                                         "Forrest Macdonald", "Thomas Barnes", "Cruz Pacheco", "Maxine Gentry",
                                         "Anika Tillman", "Robert Juarez", "Kay Buckley", "Shea Cortez",
                                         "Sylvester Roy", "Lance Little", "Kareem Mays", "Arsenio Knowles",
                                         "Colby Knapp", "Noble Warner", "Isadora Mcclure", "Katelyn Joseph",
                                         "Fletcher Jimenez", "Keaton Wolfe", "Melinda Cobb", "Aurelia Flores",
                                         "Bevis Mcdonald", "Yael Carter", "Sawyer Stokes", "Silas Battle",
                                         "Noble Gilbert", "Petra Mckenzie", "Bell Prince", "George Best", "Basil Vang",
                                         "Lael Gould", "Noel Key", "Paul Duke", "Josiah Yates", "Winifred Cantu",
                                         "Devin Abbott", "Aretha Patton", "Nell Maddox", "Tad Mack", "Amery Frazier",
                                         "Hiroko Acevedo", "Nyssa Quinn", "Iliana Porter", "Zahir Fields",
                                         "Gwendolyn Mccarty", "Victoria Solis", "Colette Sargent", "Cyrus Whitley",
                                         "Joel Rivers", "Kyra Harding", "Barrett Mckinney", "Benedict Byrd"};

static vector<int> sales_product_id = {8, 6, 7, 11, 2, 1, 5, 1, 10, 10, 6, 11, 1, 7, 4, 8, 12, 1, 10, 9, 5, 12, 3, 9, 7,
                                       3, 11, 12, 7, 7, 12, 8, 7, 8, 12, 7, 3, 2, 11, 10, 4, 12, 2, 7, 6, 5, 1, 2, 11,
                                       12, 2, 8, 11, 3, 2, 3, 6, 8, 5, 8, 1, 1, 11, 5, 9, 6, 12, 3, 8, 8, 3, 3, 1, 7, 9,
                                       10, 3, 5, 9, 1, 2, 11, 6, 12, 11, 7, 11, 6, 7, 2, 5, 12, 10, 3, 2, 5, 11, 8, 10,
                                       10};

static vector<int> sales_units = {117, 73, 205, 14, 170, 129, 82, 116, 67, 125, 71, 22, 153, 141, 65, 157, 197, 10, 30,
                                  134, 100, 142, 135, 9, 69, 189, 141, 166, 170, 199, 73, 117, 160, 45, 37, 135, 12,
                                  104, 167, 108, 105, 176, 131, 188, 93, 113, 112, 201, 41, 18, 28, 137, 95, 109, 137,
                                  196, 48, 4, 125, 211, 20, 135, 193, 184, 126, 176, 102, 203, 177, 51, 203, 106, 14,
                                  116, 7, 82, 178, 41, 85, 77, 122, 42, 64, 208, 13, 147, 163, 126, 188, 151, 89, 168,
                                  84, 16, 80, 50, 41, 19, 37, 184};

unique_ptr<Insert_plan> Insert_data::product(Global_object_store &global_object_store) {
    shared_ptr<Table> products_table = global_object_store.tables().find("product");
    shared_ptr<Table_definition> table_definition(products_table->definition());

    unique_ptr<vector<shared_ptr<Row>>> rows(new vector<shared_ptr<Row>>());

    for (size_t i = 0; i < product_name.size(); ++i) {
        shared_ptr<vector<shared_ptr<Value>>> values(new vector<shared_ptr<Value>>());
        values->push_back(unique_ptr<Value>(new Int_value((int) (i + 1))));
        values->push_back(unique_ptr<Value>(new Varchar_value(product_name[i])));
        values->push_back(unique_ptr<Value>(new Double_value(product_price[i])));

        rows->push_back(unique_ptr<Row>(new Row(values)));
    }

    unique_ptr<Plan_node> source(new Insert_data_node(table_definition, move(rows)));

    unique_ptr<Insert_plan> plan(new Insert_plan(move(source), products_table));

    return plan;
}

std::unique_ptr<db07::Insert_plan> Insert_data::sales(db07::Global_object_store &global_object_store) {
    shared_ptr<Table> sales_table = global_object_store.tables().find("sales");
    shared_ptr<Table_definition> table_definition(sales_table->definition());

    unique_ptr<vector<shared_ptr<Row>>> rows(new vector<shared_ptr<Row>>());

    for (size_t i = 0; i < sales_cust_id.size(); ++i) {
        shared_ptr<vector<shared_ptr<Value>>> values(new vector<shared_ptr<Value>>());
        values->push_back(unique_ptr<Value>(new Int_value((int) (i + 1))));
        values->push_back(unique_ptr<Value>(new Int_value(sales_cust_id[i])));
        values->push_back(unique_ptr<Value>(new Varchar_value(sales_cust_name[i])));
        values->push_back(unique_ptr<Value>(new Int_value(sales_product_id[i])));
        values->push_back(unique_ptr<Value>(new Int_value(sales_units[i])));

        rows->push_back(unique_ptr<Row>(new Row(values)));
    }

    unique_ptr<Plan_node> source(new Insert_data_node(table_definition, move(rows)));

    unique_ptr<Insert_plan> plan(new Insert_plan(move(source), sales_table));

    return plan;
}
