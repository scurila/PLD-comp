#include "IRInstr_cmpgt.h"

void IRInstr_cmpgt::gen_x86(ostream &o) {
    o   << "# cmpgt\n";

    o   <<	"  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  cmp %rbx, %rax\n"// on teste a>b  / CMP OP2, OP1 = flags = OP1 - OP2 ici a-b, on veut résultat strictement positif
        //<< "  xor %rax, %rax\n"
        << "  seta %al\n"
        << "  pushq %rax\n";

}

void IRInstr_cmpgt::gen_arm(ostream &o) {
    o << "; -- cmplt \n";
    o << "ldr x9, [sp], #16\n" // POP right member
        << "ldr x8, [sp], #16\n" // POP left member 
        << "subs x9, x9, x8\n"
        << "cset x9, lt\n"
        << "and x9, x9, #0x1\n" 
        << "str x9, [sp, #-16]!\n"; // PUSH w9
}
