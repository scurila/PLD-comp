#pragma once

#include "IR/IR.h"

#include <iostream>
#include <vector>

using namespace std;

class Program { 
public:
    Program(): current_cfg(nullptr) {}

    void add_cfg(CFG *cfg);
    void gen_asm(ostream &o, Arch arch);

    vector<CFG*> cfgList;
    CFG *current_cfg;

    // TODO will add globals table here later 

private:
    void gen_text_header(ostream &o, Arch arch);

};
