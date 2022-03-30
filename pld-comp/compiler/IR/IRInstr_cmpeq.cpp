#include "IRInstr_cmpeq.h"

void IRInstr_cmpeq::gen_x86(ostream &o) {
    o   << "# cmpeq\n";

    o   << "  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  cmp %rbx, %rax\n"//compare content of a and b
        //<< "  xor %rax, %rax\n"
        << "  sete %al\n"
        << "  pushq %rax\n";
}

void IRInstr_cmpeq::gen_arm(ostream &o) {
    o << "; -- cmpeq \n";
    o << "ldr x8, [sp], #16\n" // POP right member
        << "ldr x9, [sp], #16\n" // POP left member 
        << "subs x9, x9, x8\n"
        << "cset x9, eq\n"
        << "and x9, x9, #0x1\n" 
        << "str x9, [sp, #-16]!\n"; // push w9
}
