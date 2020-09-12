Table::Table(vector<string>& records) {
	for (std::vector<string>::iterator itr = records.begin(); itr != records.end(); ++itr) {
	    string line = trim(GetDescFromZonecost(*itr));
	    data.push_back(T(line));
	}
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

string Zonecost::GetIdFromZonecost(record item) {
    return item.substr(0, 6);
}

string Zonecost::GetDescFromZonecost(record item) {
    return item.substr(7, 20);
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
