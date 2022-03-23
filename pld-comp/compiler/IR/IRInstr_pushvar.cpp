
#include "IRInstr_pushvar.h"
#include "../Utils.h"

void IRInstr_pushvar::gen_x86(ostream &o)
{
    std::string mov = makeInstrSuffix_x86("mov", variable->type);
    std::string bp = makeRegisterName_x86("bp", variable->type);
    std::string ax = makeRegisterName_x86("ax", variable->type);

    o << "  " << mov << " " << -variable->bp_offset << "(" << bp << "), " << ax << "\n"
      << "  pushq %rax\n";
}

void IRInstr_pushvar::gen_arm(ostream &o)
{
    o << " mov w8, [sp, #" << -variable->bp_offset << "]\n"
        << " push {w8}\n";
}
