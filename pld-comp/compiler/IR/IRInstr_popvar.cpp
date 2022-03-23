
#include "IRInstr_popvar.h"
#include "../Utils.h"

void IRInstr_popvar::gen_x86(ostream &o)
{
    std::string mov = makeInstrSuffix_x86("mov", variable->type);
    std::string ax = makeRegisterName_x86("ax", variable->type);

    o << "  popq %rax\n"
      << "  " << mov << " " << ax << ", " << -variable->bp_offset << "(%rbp)\n";
}

void IRInstr_popvar::gen_arm(ostream &o)
{
    o << " pop {w8}\n"
      << " mov [sp, #" << variable->bp_offset << "], w8\n";
}
