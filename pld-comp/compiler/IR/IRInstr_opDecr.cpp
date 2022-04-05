#include "IRInstr_opDecr.h"

void IRInstr_opDecr::gen_x86 (ostream &o) {
    o   << "# opDecr\n";

    o   << "  popq %rbx\n"//a
        << "  sub $1, %rbx\n"// add a and 1
        << "  pushq %rbx\n";
}

void IRInstr_opDecr::gen_arm (ostream &o) {
    
}