#include "IRInstr_wmem.h"

void IRInstr_wmem::gen_x86 (ostream &o) {

}

void IRInstr_wmem::gen_arm (ostream &o) {
    o << "; -- wmem ";
    o << "ldr w8, [sp], #4\n" // pop w8
    << "ldr x8, [sp], #8\n" // pop x8 (64 bits)
    << "str w8 [x8]\n";
}
