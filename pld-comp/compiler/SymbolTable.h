#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include <unordered_set>

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
        SymbolTable() : topOffset(8) {}; // default to 8 to leave some space for ARM (should be handled differently later)
        bool addEntry(string name, string type);
        Entry* get(string name);
        vector<string> unusedVars();

        void push_context();
        void pop_context();

        int topOffset;

    protected: 
        vector<unordered_map<string, Entry*>*> table;

    private:
        // only stores names for popped contexts. need to call unusedVars() to get the full list
        unordered_set<string> unusedVarNames; // not very clean as shadowed variables won't be dissociated

        Entry* get(string name, int layer);
};


// TODO need global map for global variables, as symbol tables are differentiated between functions
