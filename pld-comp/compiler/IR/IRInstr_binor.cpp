
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
    
}
