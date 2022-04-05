
#include "IRInstr_opp.h"
#include "../Utils.h"

void IRInstr_opp::gen_x86(ostream &o)
{
    o << "  popq %rax\n"
      << "  negq %rax\n"
      << "  pushq %rax\n";
}

void IRInstr_opp::gen_arm(ostream &o)
{
  o << "; -- not \n";
    o << "ldr x8, [sp], #16\n" // POP right member
        << "neg x8, x8\n"
        << "str x8, [sp, #-16]!\n"; // push w8 
}
