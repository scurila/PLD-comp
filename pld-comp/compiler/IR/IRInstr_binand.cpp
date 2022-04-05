
#include "IRInstr_binand.h"
#include "../Utils.h"

void IRInstr_binand::gen_x86(ostream &o) {
    o << "# binary_and\n";

    o   << "  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  andq %rbx, %rax\n"//binary and between a and b stored in a
        << "  pushq %rax\n";

}

void IRInstr_binand::gen_arm(ostream &o) {
    o << "; -- binary_and \n";
    o << "ldr x8, [sp], #16\n" // POP right member
        << "ldr x9, [sp], #16\n" // POP left member 
        << "and x8, x8, x9\n"
        << "str x8, [sp, #-16]!\n"; // push w8 
}
