#include "database.h"
#include "utils.h"

using namespace std;

// q1
string FindZoneId(Table<Zonecost>& zonecost, string target);
vector<string> FilterCustomerWithZoneAndActive(Table<Customer>& customer, string zone_id);

//q2
vector<string> FilterProductsWithSold(Table<Lineitem>& lineitem, Table<Product>& products);

void usage() {
    cout << "usage: "  << endl;
    cout << "  <your_binary> q1 <customer.file> <zonecost.file>"  << endl;
    cout << "  <your_binary> q2 <lineitem.file> <products.file>"  << endl;
}

int main(int argc, char * argv[]) {
    if (argc != 4) {
        usage();
        return 1;
    }
    string query = argv[1];
    char* filename_1 = argv[2];
    char* filename_2 = argv[3];

    if (query.compare("q1") == 0) {
        vector<string> customer_file = ReadFile(filename_1);
        vector<string> zonecost_file = ReadFile(filename_2);

        Table<Customer> customer = new Table<Customer>(customer_file);
        Table<Zonecost> zonecost = new Table<Zonecost>(zonecost_file);

        string zone_id = FindZoneId(zonecost, "Toronto");
        vector<string> result = FilterCustomerWithZoneAndActive(customer, zone_id);
        for (std::vector<string>::iterator itr = result.begin(); itr != result.end(); ++itr) {
            cout << *itr << endl;
        }
    }
    else if (query.compare("q2") == 0 ) {
        vector<string> lineitem_file = ReadFile(filename_1);
        vector<string> products_file = ReadFile(filename_2);

        Table<Lineitem> lineitem = new Table<Lineitem>(lineitem_file);
        Table<Product> products = new Table<Product>(products_file);

        vector<string> result = FilterProductsWithSold(lineitem, products);
        for (std::vector<string>::iterator itr = result.begin(); itr != result.end(); ++itr) {
            cout << *itr << endl;
        }
    }
    else {
        usage();
        return 1;
    }
    return 0;
}

//===========================================

string FindZoneId(Table<Zonecost>& zonecost, string target) {
    for (std::vector<Zonecost>::const_iterator itr = zonecost.data.begin(); itr != zonecost.data.end(); ++itr) {
        string desc = (*itr).ZONEDESC;
        if (desc.compare(target) == 0) {
            return (*itr).ZONEID;
        }
    }
    // no target record in zonecost.
    // return invalid zone id.
    return "XXXXXX";
}

vector<string> FilterCustomerWithZoneAndActive(Table<Customer>& customer, string zone_id) {
    vector<string> result;
    for (std::vector<Customer>::const_iterator itr = customer.data.begin(); itr != customer.data.end(); ++itr) {
        string zone = (*itr).ZONE;
        string active = (*itr).ACTIVE;

        if(zone.compare(zone_id) == 0 && active.compare("1") == 0) {
            string lname = (*itr).LNAME;
            result.push_back(lname);
        }
    }
    return result;
}

vector<string> FilterProductsWithSold(Table<Lineitem>& lineitem, Table<Product>& products) {
    vector<string> result;
    for (std::vector<Product>::const_iterator itr = products.data.begin(); itr != products.data.end(); ++itr) {
        string barcode = (*itr).BARCODE;

        int customer_cnt = 0;
        string name = "";
        for (std::vector<Lineitem>::const_iterator line_itr = lineitem.data.begin(); line_itr != lineitem.data.end(); ++line_itr) {
            string line_barcode = (*line_itr).BARCODE;
            if (line_barcode.compare(barcode) == 0) {
                string new_name = (*line_itr).UNAME;
                if (customer_cnt == 0) {
                    customer_cnt++;
                    name = new_name;
                }
                else {
                    if (name.compare(new_name) != 0) {
                        customer_cnt++;
                        break;
                    }
                }
            }
        }

        if (customer_cnt == 2) {
            string desc = (*itr).PRODDESC;
            result.push_back(barcode + "    " + desc);
        }
    }
    return result;
}

