#include "database.h"
#include "utils.h"

using namespace std;

void Usage() {
    cout << "usage: "  << endl;
    cout << "  <your_binary> q1 <customer.file> <zonecost.file>"  << endl;
    cout << "  <your_binary> q2 <lineitem.file> <products.file>"  << endl;
}

int main(int argc, char * argv[]) {
    if (argc != 4) {
        Usage();
        return 1;
    }
    string query = argv[1];
    char* filename_1 = argv[2];
    char* filename_2 = argv[3];

    if (query.compare("q1") == 0) {
        vector<string> customer_file = ReadFile(filename_1);
        vector<string> zonecost_file = ReadFile(filename_2);

        CustomerTable customer = CustomerTable(customer_file);
        ZonecostTable zonecost = ZonecostTable(zonecost_file);

        vector<string> zone_ids = zonecost.FindZoneId("Toronto");
        vector<string> result = customer.FilterZoneAndActive(zone_ids);
        for (std::vector<string>::iterator itr = result.begin(); itr != result.end(); ++itr) {
            cout << *itr << endl;
        }
    }
    else if (query.compare("q2") == 0 ) {
        vector<string> lineitem_file = ReadFile(filename_1);
        vector<string> products_file = ReadFile(filename_2);

        LineitemTable lineitem = LineitemTable(lineitem_file);
        ProductTable products = ProductTable(products_file);

        vector<string> result = products.FilterSoldByTwoCustomer(lineitem);
        for (std::vector<string>::iterator itr = result.begin(); itr != result.end(); ++itr) {
            cout << *itr << endl;
        }
    }
    else {
        Usage();
        return 1;
    }
    return 0;
}

