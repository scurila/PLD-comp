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

}
