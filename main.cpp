using namespace std;

int main(int argc, char * argv[]) {
    if (argc != 4) {
        usage();
        return 1;
    }
    string query = argv[1];
    string filename_1 = argv[2];
    string filename_2 = argv[3];

    if (query.compare("q1") == 0) {
        vector<record> customer = ReadFile(filename_1);
        vector<record> zonecost = ReadFile(filename_2);
        int zone_id = FindZoneId(zonecost, "Toronto");
        vector<string> result = FilterZoneAndActive(customer, zone_id);
        cout << result << endl;
    }
    else if (query.compare("q2") == 0 ) {
        vector<record> lineitem = ReadFile(filename_1);
        vector<record> products = ReadFile(filename_2);
        vector<string> result FilterProductsWithSold(lineitem, products);
        cout << result << endl;
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
    vector<recore> result;
    ifstream rf(filename);
    if(rf.is_open() ) {
        string line;
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
    for (std::vector<record>::iterator itr = zonecost.begin(); itr != zonecost.end(); ++itr) {
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
    for (std::vector<record>::iterator itr = customer.begin(); itr != customer.end(); ++itr) {
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
    return item.substr(42, 63);
}

string GetZoneFromCustomer(record item) {
    return item.substr(135, 142);
}

string GetActiveFromCustomer(record item) {
    return item.substr(243, 250);
}
