#include "IRInstr_copy.h"
#include "../Exceptions.h"

void IRInstr_copy::gen_x86(ostream &o) {
    o << "# copy\n";
    try {
		o 
			<< "  movl "<< -1* symbolTable()->get(val)->bp_offset <<"(%rbp), " << "(%eax)\n";
		o
			<< "  movl %eax, " <<  -1*symbolTable()->get(dest)->bp_offset <<"(%rbp)\n";	
	} catch (UndeclaredVarException e) {
		errorMessage(e.message());
	}
}

void IRInstr_copy::gen_arm(ostream &o) {
     o << "; -- copy\n";
    try {
		o 
			<< "  ldr w8, [sp, #"<< -1* symbolTable()->get(val)->bp_offset <<"]\n";
		o
			<< "  str w8, [sp, #" <<  -1*symbolTable()->get(dest)->bp_offset <<"]\n";	
	} catch (UndeclaredVarException e) {
		errorMessage(e.message());
	}
}