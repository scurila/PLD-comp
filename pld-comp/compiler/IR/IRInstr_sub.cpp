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
    o << "ldr w8, [sp], #4\n" // POP right member
	<< "ldr w9, [sp], #4\n" // POP left member 
	<< "sub w9, w9, w8\n"
	<< "str w9, [sp, #-4]!\n"; // push w9
}
