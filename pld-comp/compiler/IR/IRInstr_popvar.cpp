
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
    o << "; -- ldconst \n";
    o << "ldr w8, [sp], #4\n" // pop w8
      << "mov [x29, #" << -1*variable->bp_offset << "], w8\n";
}
