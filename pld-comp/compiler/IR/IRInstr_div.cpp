#include "IRInstr_div.h"

void IRInstr_div::gen_x86 (ostream &o) {
    o << "# divide\n";

    o   << "  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  cdq\n"//32 bit dividend 
    	<< "  idivq %rbx\n"//The idiv instruction divides the contents of the 64-bit integer EDX:EAX by the specified operand value.
    	<< "  pushq %rax\n";//The quotient result of the division is stored into EAX
}

void IRInstr_div::gen_arm (ostream &o) {
    o << "; -- divide\n";

    o << "ldr x8, [sp], #16\n" // POP right member
	<< "ldr x9, [sp], #16\n" // POP left member 
	<< "sdiv x9, x9, x8\n"
	<< "str x9, [sp, #-16]!\n"; // push w9
}
