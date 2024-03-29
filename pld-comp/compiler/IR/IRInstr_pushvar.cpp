
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
    o << "ldr x3, [x29, #" << -1*variable->bp_offset << "]\n" 
        << "str x3, [sp, #-16]!\n"; // push w3
}
