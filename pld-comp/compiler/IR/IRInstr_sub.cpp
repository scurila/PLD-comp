#include "IRInstr_sub.h"

void IRInstr_sub::gen_x86(ostream &o){
    o   << "# sub\n";

    o   << "  popq %rbx\n"//right member
    	<< "  popq %rax\n"//left member
    	<< "  sub %rbx, %rax\n"//substract b from a and stores result in a
    	<< "  pushq %rax\n";
}

void IRInstr_sub::gen_arm (ostream &o){
    o << "; -- sub \n";
    o << "ldr x8, [sp], #16\n" // POP right member
	<< "ldr x9, [sp], #16\n" // POP left member 
	<< "sub x9, x9, x8\n"
	<< "str x9, [sp, #-16]!\n"; // push w9
}
