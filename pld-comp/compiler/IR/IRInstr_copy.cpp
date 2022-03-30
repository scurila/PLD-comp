#include "IRInstr_copy.h"
#include "../Exceptions.h"

// TODO does not handle dynamic type sizes (only int for now)

void IRInstr_copy::gen_x86(ostream &o) {
    o << "# copy\n";
    try {
		o 
			<< "  movl "<< -1* symbolTable()->get(val)->bp_offset <<"(%rbp), " << "%eax\n";
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
			<< "ldr x8, [x29, #"<< -1*symbolTable()->get(val)->bp_offset <<"]\n";
		o
			<< "str x8, [x29, #" << -1*symbolTable()->get(dest)->bp_offset <<"]\n";	
	} catch (UndeclaredVarException e) {
		errorMessage(e.message());
	}
}
