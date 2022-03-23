#include "IRInstr_rmem.h"

void IRInstr_rmem::gen_x86 (ostream &o) {

}

void IRInstr_rmem::gen_arm (ostream &o) {
    o << "; -- wmem ";
    o << "  pop {w8}\n"
    << "    pop {x8}\n"
    << "    str w8 [x8]\n";
}
