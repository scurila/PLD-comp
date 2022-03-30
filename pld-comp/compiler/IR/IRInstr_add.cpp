#include "IRInstr_add.h"

void IRInstr_add::gen_x86(ostream &o) {
    o << "# add\n";
    o << "  popq %rbx\n"//right member
      << "  popq %rax\n"//left member
      << "  add %rbx, %rax\n"// add a and b and stores result in a
      << "  pushq %rax\n";
}

void IRInstr_add::gen_arm(ostream &o) {
    o << "; -- add \n";
    o << "ldr x8, [sp], #16\n" // POP right member
        << "ldr x9, [sp], #16\n" // POP left member 
        << "add x8, x8, x9\n"
        << "str x8, [sp, #-16]!\n"; // push w8 
}
