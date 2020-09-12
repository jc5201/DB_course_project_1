#include "main.h"
using namespace std;

int main(int argc, char * argv[]) {
    if (argc != 4) {
        usage();
        return 1;
    }
    string query = argv[1];
    char* filename_1 = argv[2];
    char* filename_2 = argv[3];

    if (query.compare("q1") == 0) {
        vector<record> customer = ReadFile(filename_1);
        vector<record> zonecost = ReadFile(filename_2);
        string zone_id = FindZoneId(zonecost, "Toronto");
        vector<string> result = FilterCustomerWithZoneAndActive(customer, zone_id);
        for (std::vector<record>::iterator itr = result.begin(); itr != result.end(); ++itr) {
            cout << *itr << endl;
        }
    }
    else if (query.compare("q2") == 0 ) {
        vector<record> lineitem = ReadFile(filename_1);
        vector<record> products = ReadFile(filename_2);
        vector<string> result = FilterProductsWithSold(lineitem, products);
        for (std::vector<record>::iterator itr = result.begin(); itr != result.end(); ++itr) {
            cout << *itr << endl;
        }
    }
    else {
        usage();
        return 1;
    }
    return 0;
}

void usage() {
    cout << "usage: "  << endl;
    cout << "  <your_binary> q1 <customer.file> <zonecost.file>"  << endl;
    cout << "  <your_binary> q2 <lineitem.file> <products.file>"  << endl;
}

string trim(const string& s) {
    int i = s.find_last_not_of(" \t\r\n");
    return i == string::npos ? s : s.substr(0, i + 1);
}

vector<record> ReadFile(char * filename) {
    vector<record> result;
    ifstream rf(filename);
    if(rf.is_open() ) {
        string line;
        //skip 2 lines
        getline(rf, line);
        getline(rf, line);

        while(getline(rf, line)) {
            result.push_back(line);
        }
        rf.close();
    }
    return result;
}

string FindZoneId(const vector<record> zonecost, string target) {
    for (std::vector<record>::const_iterator itr = zonecost.begin(); itr != zonecost.end(); ++itr) {
        string desc = trim(GetDescFromZonecost(*itr));
        if (desc.compare(target) == 0) {
            return trim(GetIdFromZonecost(*itr));
        }
    }
    // no target record in zonecost.
    // return invalid zone id.
    return "XXXXXX";
}

vector<string> FilterCustomerWithZoneAndActive(const vector<record> customer, string zone_id) {
    vector<string> result;
    for (std::vector<record>::const_iterator itr = customer.begin(); itr != customer.end(); ++itr) {
        string zone = trim(GetZoneFromCustomer(*itr));
        string active = trim(GetActiveFromCustomer(*itr));

        if(zone.compare(zone_id) == 0 && active.compare("1") == 0) {
            string lname = trim(GetLnameFromCustomer(*itr));
            result.push_back(lname);
        }
    }
    return result;
}

string GetLnameFromCustomer(record item) {
    return item.substr(42, 20);
}

string GetZoneFromCustomer(record item) {
    return item.substr(135, 6);
}

string GetActiveFromCustomer(record item) {
    return item.substr(243, 6);
}

string GetIdFromZonecost(record item) {
    return item.substr(0, 6);
}

string GetDescFromZonecost(record item) {
    return item.substr(7, 20);
}

vector<string> FilterProductsWithSold(const vector<record> lineitem, const vector<record> products) {
    vector<string> result;
    for (std::vector<record>::const_iterator itr = products.begin(); itr != products.end(); ++itr) {
        string barcode = trim(GetBarcodeFromProducts(*itr));

        int customer_cnt = 0;
        string name = "";
        for (std::vector<record>::const_iterator line_itr = lineitem.begin(); line_itr != lineitem.end(); ++line_itr) {
            string line_barcode = trim(GetBarcodeFromLineitem(*line_itr));
            if (line_barcode.compare(barcode) == 0) {
                string new_name = trim(GetUnameFromLineitem(*line_itr));
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
            string barcode = GetBarcodeFromProducts(*itr);
            string desc = GetDescFromProducts(*itr);
            result.push_back(barcode + desc);
        }
    }
    return result;
}

string GetUnameFromLineitem(record item) {
    return item.substr(0, 20);
}

string GetBarcodeFromLineitem(record item) {
    return item.substr(41, 20);
}

string GetBarcodeFromProducts(record item) {
    return item.substr(0, 20);
}

string GetDescFromProducts(record item) {
    return item.substr(32, 50);
}

