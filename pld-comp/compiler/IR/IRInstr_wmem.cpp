#include "IRInstr_wmem.h"

void IRInstr_wmem::gen_x86 (ostream &o) {

}

void IRInstr_wmem::gen_arm (ostream &o) {
    o << "; -- wmem ";
    o << "ldr x9, [sp], #16\n" // pop w8
    << "ldr x8, [sp], #16\n" // pop x8 (64 bits)
    << "str x9 [x8]\n";
}
