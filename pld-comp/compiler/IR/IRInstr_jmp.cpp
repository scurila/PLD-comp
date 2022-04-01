
#include "IRInstr_jmp.h"

void IRInstr_jmp::gen_x86(ostream &o)
{
    o << "  jmp " << jumpLabel << "\n";
}

void IRInstr_jmp::gen_arm(ostream &o)
{
    o << "  bl" << jumpLabel << "\n";
}
