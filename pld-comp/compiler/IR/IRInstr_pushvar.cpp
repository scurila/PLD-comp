
#include "IRInstr_pushvar.h"
#include "../Utils.h"

void IRInstr_pushvar::gen_x86(ostream &o)
{
    std::string mov = makeInstrSuffix_x86("mov", variable->type);
    std::string ax = makeRegisterName_x86("ax", variable->type);

    o << "  " << mov << " " << -variable->bp_offset << "(%rbp), " << ax << "\n"
      << "  pushq %rax\n";
}

void IRInstr_pushvar::gen_arm(ostream &o)
{
    o << "; -- pushvar \n";
    o << "mov w8, [sp, #" << variable->bp_offset << "]\n"
        << "push {w8}\n";
}
