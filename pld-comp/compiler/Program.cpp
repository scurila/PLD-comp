
#include "Program.h"

#include <iostream>
#include <vector>

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

