#include "IRInstr_div.h"

void IRInstr_div::gen_x86 (ostream &o) {
    o << "# divide\n";

    o   << "  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
    	<< "  idiv %rbx\n"//The idiv instruction divides the contents of the 64-bit integer EDX:EAX by the specified operand value.
    	<< "  pushq %rax\n";//The quotient result of the division is stored into EAX

}

void IRInstr_div::gen_arm (ostream &o) {

}