#ifndef DB_H_
#define DB_H_

#include<iostream>
#include<vector>
#include<set>
#include<string>

#include "utils.h"

using namespace std;

template <typename T>
class Table {
public:
    vector<T> data;

    Table(vector<string>& records) {
        for (std::vector<string>::iterator itr = records.begin(); itr != records.end(); ++itr) {
            string line = (*itr);
            data.push_back(T(line));
        }
    }
};

class Customer {
public:
    string LNAME;
    string ZONE;
    string ACTIVE;

    Customer(string record) {
        LNAME = trim(GetLnameFromCustomer(record));
        ZONE = trim(GetZoneFromCustomer(record));
        ACTIVE = trim(GetActiveFromCustomer(record));
    }

private : 
    string GetLnameFromCustomer(string item);
    string GetZoneFromCustomer(string item);
    string GetActiveFromCustomer(string item);
};

class Zonecost {
public:
    string ZONEID;
    string ZONEDESC;

    Zonecost(string record) {
        ZONEID = trim(GetIdFromZonecost(record));
        ZONEDESC = trim(GetDescFromZonecost(record));
    }

private : 
    string GetIdFromZonecost(string item);
    string GetDescFromZonecost(string item);
};

class Lineitem {
public:
    string UNAME;
    string BARCODE;

    Lineitem(string record) {
        UNAME = trim(GetUnameFromLineitem(record));
        BARCODE = trim(GetBarcodeFromLineitem(record));
    }

private : 
    string GetUnameFromLineitem(string item);
    string GetBarcodeFromLineitem(string item);
};

class Product {
public:
    string BARCODE;
    string PRODDESC;

    Product(string record) {
        BARCODE = trim(GetBarcodeFromProducts(record));
        PRODDESC = trim(GetDescFromProducts(record));
    }

private : 
    string GetBarcodeFromProducts(string item);
    string GetDescFromProducts(string item);
};

class CustomerTable : Table<Customer> {
public:
    CustomerTable(vector<string>& records) : Table<Customer>(records) {};
    vector<string> FilterZoneAndActive(vector<string> zone_ids);
};

class ZonecostTable : Table<Zonecost> {
public:
    ZonecostTable(vector<string>& records) : Table<Zonecost>(records) {};
    vector<string> FindZoneId(string target);
};

class LineitemTable : Table<Lineitem> {
public:
    LineitemTable(vector<string>& records) : Table<Lineitem>(records) {};
    set<string> UnamesBoughtProduct(string barcode);
};

class ProductTable : Table<Product> {
public:
    ProductTable(vector<string>& records) : Table<Product>(records) {};
    vector<string> FilterSoldByTwoCustomer(LineitemTable& lineitem);
};

#endif 
