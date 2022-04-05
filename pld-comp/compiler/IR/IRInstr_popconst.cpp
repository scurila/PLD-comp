#include "IRInstr_popconst.h"

void IRInstr_popconst::gen_x86(ostream &o)
{
    o << "# popconst\n";

    o << "  popq %rax\n";
}

void IRInstr_popconst::gen_arm(ostream &o)
{
    o << "ldr x0, [sp], #16\n";
}
