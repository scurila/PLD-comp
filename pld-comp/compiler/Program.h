#pragma once

#include "IR/IR.h"

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef enum _global_entry_type {
    func,
    variable  // for later use
} gentry_t;

class GlobalsEntry {
public:
    GlobalsEntry(string name, string type): name(name), type(type) {}

    string name;
    string type;
    
    gentry_t entryType; 
};

class FuncEntry : public GlobalsEntry {
public:
    FuncEntry(string name, string type): GlobalsEntry(name, type)  {
        entryType = func;
    }

    vector<string> arglist;  // only arg types required
};


class GlobalsTable {
public:
    GlobalsTable() {}

    void register_global(GlobalsEntry *new_entry);
    GlobalsEntry *find_global(string name);

private:
    unordered_map<string, GlobalsEntry*> globals;
};

class Program { 
public:
    Program(): current_cfg(nullptr) {}

    void add_cfg(CFG *cfg);
    void gen_asm(ostream &o, Arch arch);

    vector<CFG*> cfgList;
    CFG *current_cfg;

    // TODO will add globals table here later 
    GlobalsTable *globals_table;

private:
    void gen_text_header(ostream &o, Arch arch);

};
