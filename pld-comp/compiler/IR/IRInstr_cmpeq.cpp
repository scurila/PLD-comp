#include "IRInstr_cmpeq.h"

void IRInstr_cmpeq::gen_x86(ostream &o) {
    o   << "# cmpeq\n";

    o   <<	"  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  cmp %rbx, %rax\n"//compare content of a and b
        << "  sete %rax\n"
        << "  pushq %rax\n";
}

void IRInstr_cmpeq::gen_arm(ostream &o) {
    o << "; -- cmpeq \n";
    o << "pop {w8}\n" // right member
        << "pop {w9}\n" // left member 
        << "subs w9, w9, w8\n"
        << "cset w9, eq\n"
        << "and w9, w9, #0x1\n" 
        << "push {w9}\n";
}
