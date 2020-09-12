string trim(const string& s) {
    int i = s.find_last_not_of(" \t\r\n");
    return i == string::npos ? s : s.substr(0, i + 1);
}

vector<string> ReadFile(char * filename) {
    vector<string> result;
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

