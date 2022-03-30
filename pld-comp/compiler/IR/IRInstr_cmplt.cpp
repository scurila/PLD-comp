#include "IRInstr_cmplt.h"

void IRInstr_cmplt::gen_x86(ostream &o) {
    o   << "# cmplt\n";

    o   <<	"  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  cmp %rbx, %rax\n"// on teste a<b  / CMP OP2, OP1 = flags = OP1 - OP2 ici a-b, on veut résultat strictement négatif
        //<< "  xor %rax, %rax\n"
        << "  setb %al\n"
        << "  pushq %rax\n";
}

void IRInstr_cmplt::gen_arm(ostream &o) {
    o << "; -- cmplt \n";
    o << "ldr w8, [sp], #4\n" // POP right member
        << "ldr w9, [sp], #4\n" // POP left member 
        << "subs w9, w9, w8\n"
        << "cset w9, lt\n"
        << "and w9, w9, #0x1\n" 
        << "str w9, [sp, #-4]!\n"; // PUSH w9
}
