#include <unordered_map>
#include <string>
#include <utility>

using namespace std;

class Entry {
    public:
        Entry(string n, string t, int o, int s) : name(n), type(t), bp_offset(o), size(s) {};
        string name; 
        string type;
        int bp_offset;
        int size; 
};

class SymbolTable {
    public:
        SymbolTable() : topOffset(0) {};
        bool addEntry(string name, string type, int size);
        Entry* get(string name);
    protected: 
        unordered_map<string, Entry*> table;
        int topOffset;
};
