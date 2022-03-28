#include "IRInstr_mul.h"

void IRInstr_mul::gen_x86 (ostream &o) {
    o   << "# mult\n";

    o   <<	"  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  imul %rbx, %rax\n"//signed multiplication between a and b stored in a
        << "  pushq %rax\n";
}

void IRInstr_mul::gen_arm (ostream &o) {
    o << "; -- mul \n";
    o << "ldr w8, [sp], #4\n" // POP right member
	<< "ldr w9, [sp], #4\n" // POP left member 
	<< "mul w9, w9, w8\n"
	<< "str w9, [sp, #-4]!\n"; // push w9
}
