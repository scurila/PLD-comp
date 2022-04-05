
#include "IRInstr_binor.h"
#include "../Utils.h"

void IRInstr_binor::gen_x86(ostream &o) {
    o << "# binary_or\n";

    o   << "  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  orq %rbx, %rax\n"//binary and between a and b stored in a
        << "  pushq %rax\n";

}

void IRInstr_binor::gen_arm(ostream &o) {
    o << "; -- binary_or \n";
    o << "ldr x8, [sp], #16\n" // POP right member
        << "ldr x9, [sp], #16\n" // POP left member 
        << "orr x8, x8, x9\n"
        << "str x8, [sp, #-16]!\n"; // push w8 
}
