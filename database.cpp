#include "database.h"
using namespace std;

vector<string> CustomerTable::FilterZoneAndActive( vector<string> zone_id) {
    vector<string> result;
    for (std::vector<Customer>::const_iterator itr = this->data.begin(); itr != this->data.end(); ++itr) {
        string zone = (*itr).ZONE;
        string active = (*itr).ACTIVE;

        for (std::vector<string>::const_iterator zone_itr = zone_id.begin(); zone_itr != zone_id.end(); ++zone_itr) {
            string target = (*zone_itr);
            if(zone.compare(target) == 0 && active.compare("1") == 0) {
                string lname = (*itr).LNAME;
                result.push_back(lname);
                break;
            }
        }
    }
    return result;
}

vector<string> ZonecostTable::FindZoneId(string target) {
    vector<string> result;
    for (std::vector<Zonecost>::const_iterator itr = this->data.begin(); itr != this->data.end(); ++itr) {
        string desc = (*itr).ZONEDESC;
        if (desc.compare(target) == 0) {
            result.push_back((*itr).ZONEID);
        }
    }
    return result;
}


vector<string> ProductTable::FilterSoldByTwoCustomer(LineitemTable& lineitem) {
    vector<string> result;
    for (std::vector<Product>::const_iterator itr = this->data.begin(); itr != this->data.end(); ++itr) {
        string barcode = (*itr).BARCODE;

        int customer_cnt = lineitem.UnamesBoughtProduct(barcode).size();
        if (customer_cnt >= 2) {
            string desc = (*itr).PRODDESC;
            result.push_back(barcode + "    " + desc);
        }
    }
    return result;
}

set<string> LineitemTable::UnamesBoughtProduct(string barcode) {
    set<string> result;
	for (std::vector<Lineitem>::const_iterator itr = this->data.begin(); itr != this->data.end(); ++itr) {
		string line_barcode = (*itr).BARCODE;
        if (line_barcode.compare(barcode) == 0) {
            string name = (*itr).UNAME;
            result.insert(name);
        }
	}
	return result;
}


string Customer::GetLnameFromCustomer(string item) {
    return item.substr(42, 20);
}

string Customer::GetZoneFromCustomer(string item) {
    return item.substr(135, 6);
}

string Customer::GetActiveFromCustomer(string item) {
    return item.substr(243, 6);
}

string Zonecost::GetIdFromZonecost(string item) {
    return item.substr(0, 6);
}

string Zonecost::GetDescFromZonecost(string item) {
    return item.substr(7, 20);
}

string Lineitem::GetUnameFromLineitem(string item) {
    return item.substr(0, 20);
}

string Lineitem::GetBarcodeFromLineitem(string item) {
    return item.substr(41, 20);
}

string Product::GetBarcodeFromProducts(string item) {
    return item.substr(0, 20);
}

string Product::GetDescFromProducts(string item) {
    return item.substr(32, 50);
}
