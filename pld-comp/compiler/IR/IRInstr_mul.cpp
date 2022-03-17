#include "IRInstr_mul.h"

void IRInstr_mul::gen_x86 (ostream &o) {
    o   << "# mult\n";

    o   <<	"  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  imul %rbx, %rax\n"//signed multiplication between a and b stored in a
        << "  pushq %rax\n";
}

void IRInstr_mul::gen_arm (ostream &o) {

}