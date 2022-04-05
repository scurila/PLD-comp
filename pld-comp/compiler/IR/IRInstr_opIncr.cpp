#include "IRInstr_opIncr.h"

void IRInstr_opIncr::gen_x86 (ostream &o) {
    o   << "# opIncr\n";

    o   << "  popq %rbx\n"//a
        << "  add $1, %rbx\n"// add a and 1
        << "  pushq %rbx\n";
}

void IRInstr_opIncr::gen_arm (ostream &o) {
    
}