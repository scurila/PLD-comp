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
    o << "ldr x8, [sp], #16\n" // POP right member
	<< "ldr x9, [sp], #16\n" // POP left member 
	<< "mul x9, x9, x8\n"
	<< "str x9, [sp, #-16]!\n"; // push w9
}
