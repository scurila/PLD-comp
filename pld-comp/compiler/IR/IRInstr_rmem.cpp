#include "IRInstr_rmem.h"

void IRInstr_rmem::gen_x86 (ostream &o) {

}

void IRInstr_rmem::gen_arm (ostream &o) {
    o << "; -- rmem ";
    o << "pop {x8}\n"
    << "ldr w8 [x8]\n"
    << "push {w8}";
}
