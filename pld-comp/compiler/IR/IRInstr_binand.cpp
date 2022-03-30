
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
    
}
