
#include "IRInstr_binand.h"
#include "../Utils.h"

void IRInstr_binand::gen_x86(ostream &o) {
   o << "# binary_and\n";

    o   << "  movq %rbx\n"//right member
        << "  movq %rax\n"//left member
        << "  bit_andq %rax,%rbx\n"//binary and
    	<< "  pushq %rax\n";//The quotient result of the division is stored into EAX  

}

void IRInstr_binand::gen_arm(ostream &o) {
    
}
