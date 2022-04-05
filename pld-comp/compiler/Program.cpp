
#include "Program.h"
#include "Exceptions.h"

#include <iostream>
#include <vector>

// Program methods

void Program::add_cfg(CFG *cfg) {
    cfgList.push_back(cfg);
}

void Program::gen_asm(ostream &o, Arch arch) {
    gen_text_header(o, arch);

    for(auto &cfg : cfgList) {
        cfg->gen_asm(o, arch);
    }
}

void Program::gen_text_header(ostream &o, Arch arch) {
    if(arch == x86) {
        o << ".text\n";
    }
    else if(arch == arm) {
        o << ".section	__TEXT,__text,regular,pure_instructions\n"
          << ".build_version macos, 12, 0	sdk_version 12, 3\n";
    }
}


// Globals methods
GlobalsEntry *GlobalsTable::find_global(string name) {
    if(globals.find(name) == globals.end()) {
        throw new UndeclaredNameException(name);
    }

    return globals[name];
}

void GlobalsTable::register_global(GlobalsEntry *new_entry) {
    if(globals.find(new_entry->name) != globals.end()) {
        throw new NameAlreadyDefinedException(new_entry->name);
    }

    globals.insert(make_pair(new_entry->name, new_entry));
}
