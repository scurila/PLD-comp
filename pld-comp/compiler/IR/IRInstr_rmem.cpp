#include "IRInstr_rmem.h"

void IRInstr_rmem::gen_x86 (ostream &o) {

}

void IRInstr_rmem::gen_arm (ostream &o) {
    o << "; -- rmem ";
    o << "ldr x9, [sp], #16\n" // pop x9 (64bits)
    << "ldr x8 [x9]\n" 
    << "str x8, [sp, #-16]!\n"; // push w8 (32 bits)
}
