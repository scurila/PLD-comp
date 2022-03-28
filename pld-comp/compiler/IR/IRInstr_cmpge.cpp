#include "IRInstr_cmpge.h"

void IRInstr_cmpge::gen_x86(ostream &o) {
    o   << "# cmpge\n";

    o   <<	"  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  cmp %rbx, %rax\n"// on teste a>=b  / CMP OP2, OP1 = flags = OP1 - OP2 ici a-b, on veut résultat positif
        << "  xor %rax, %rax\n"
        << "  setae %al\n"
        << "  pushq %rax\n";
}

void IRInstr_cmpge::gen_arm(ostream &o) {

}
