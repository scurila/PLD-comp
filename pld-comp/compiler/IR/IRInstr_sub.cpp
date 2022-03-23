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
    o << "  pop {w8}\n" // right member
	<< "   pop {w9}\n" // left member 
	<< "   sub w9, w9, w8\n"
	<< "   push {w9}\n";
}
