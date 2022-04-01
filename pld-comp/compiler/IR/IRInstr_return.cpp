
#include "IRInstr_return.h"

void IRInstr_return::gen_x86(ostream &o)
{
    if(hasValue) {
        o << "  popq %rax\n";
    }

    o << "  jmp " << bb->cfg->get_epilogue_label(x86) << "\n";
}

void IRInstr_return::gen_arm(ostream &o)
{
    if(hasValue) {
        o << "ldr x0, [sp], #16\n"; // POP w0 : lire [sp], puis pop de 4 (wX 32 bits)
    }

    o << "  bl" << bb->cfg->get_epilogue_label(arm) << "\n";
}
