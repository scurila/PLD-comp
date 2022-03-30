#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <utility>

using namespace std;

/*enum VarTypes { INT, CHAR };
const string VarTypeName[] = { "int", "char" };
const int VarTypeSize[] = { 4, 4 };
*/
class Entry {
    public:
        Entry(string n, string t, int o, int s) : name(n), type(t), bp_offset(o), size(s), used(false) {};
        string name; 
        string type;
        int bp_offset;
        int size; 
        bool used; // todo : discuss (used = assigned val or read for now, do two flags initialized & read ?)
};

class SymbolTable {
    public:
        SymbolTable() : topOffset(16) {}; // default to 16 for the backup of the frame variables
        bool addEntry(string name, string type);
        Entry* get(string name);
        vector<string> unusedVars();
        int topOffset;
    protected: 
        unordered_map<string, Entry*> table;
        
};
