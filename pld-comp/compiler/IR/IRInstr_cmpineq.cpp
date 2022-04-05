#include "IRInstr_cmpineq.h"

void IRInstr_cmpineq::gen_x86(ostream &o) {
    o   << "# cmpineq\n";

    o   <<	"  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  cmp %rbx, %rax\n"//compare content of a and b
        //<< "  xor %rax, %rax\n"
        << "  setnz %al\n"
        << "  pushq %rax\n";
}

void IRInstr_cmpineq::gen_arm(ostream &o) {
    o << "; -- cmplt \n";
    o << "ldr x8, [sp], #16\n" // POP right member
        << "ldr x9, [sp], #16\n" // POP left member 
        << "cmp x8, x9\n"
        << "cset x9, ne\n"
        << "and x9, x9, #0x1\n" 
        << "str x9, [sp, #-16]!\n"; // PUSH w9 
}
