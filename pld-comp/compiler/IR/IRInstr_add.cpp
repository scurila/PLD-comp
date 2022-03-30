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
    o << "ldr w8, [sp], #4\n" // POP right member
        << "ldr w9, [sp], #4\n" // POP left member 
        << "add w8, w8, w9\n"
        << "str w8, [sp, #-4]!\n"; // push w8 
}
