#include "database.h"
using namespace std;

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
