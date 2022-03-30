#include "IRInstr_mod.h"

void IRInstr_mod::gen_x86 (ostream &o) {
    o << "# modulo\n";

    o   << "  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  cdq\n"//32 bit dividend 
    	<< "  idivq %rbx\n"//The idiv instruction divides the contents of the 64-bit integer EDX:EAX by the specified operand value.
    	<< "  pushq %rdx\n";//The result of the division is stored into RDX
}

void IRInstr_mod::gen_arm (ostream &o) {
}
