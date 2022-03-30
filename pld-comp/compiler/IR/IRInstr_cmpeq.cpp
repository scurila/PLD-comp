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
    o << "ldr w8, [sp], #4\n" // POP right member
        << "ldr w9, [sp], #4\n" // POP left member 
        << "subs w9, w9, w8\n"
        << "cset w9, eq\n"
        << "and w9, w9, #0x1\n" 
        << "str w9, [sp, #-4]!\n"; // push w9
}
