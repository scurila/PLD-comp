#include "IRInstr_rmem.h"

void IRInstr_rmem::gen_x86 (ostream &o) {

}

void IRInstr_rmem::gen_arm (ostream &o) {
    o << "; -- rmem ";
    o << "ldr x8, [sp], #8\n" // pop x8 (64bits)
    << "ldr w8 [x8]\n" 
    << "str w8, [sp, #-4]!\n"; // push w8 (32 bits)
}
