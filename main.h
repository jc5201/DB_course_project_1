#ifndef MAIN_H_
#define MAIN_H_

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

typedef string record;

int main(int argc, char * argv[]);
void usage();
vector<record> ReadFile(char * filename);
string trim(const string& str);

// q1
string FindZoneId(const vector<record> zonecost, string target);
vector<string> FilterCustomerWithZoneAndActive(const vector<record> customer, string zone_id);

string GetLnameFromCustomer(record item);
string GetZoneFromCustomer(record item);
string GetActiveFromCustomer(record item);

string GetIdFromZonecost(record item);
string GetDescFromZonecost(record item);

//q2
vector<string> FilterProductsWithSold(const vector<record> lineitem, const vector<record> products);

string GetUnameFromLineitem(record item);
string GetBarcodeFromLineitem(record item);

string GetBarcodeFromProducts(record item);
string GetDescFromProducts(record item);

#endif 
