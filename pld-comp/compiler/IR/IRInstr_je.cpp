
#include "IRInstr_je.h"

void IRInstr_je::gen_x86(ostream &o)
{
    o << "  popq %rax\n"
      << "  popq %rbx\n"
      << "  cmp %rax, %rbx\n"
      << "  je " << jumpLabel << "\n";
}

void IRInstr_je::gen_arm(ostream &o)
{
  o << "; -- cmplt \n";
    o << "ldr x8, [sp], #16\n" // POP right member
        << "ldr x9, [sp], #16\n" // POP left member 
        << "cmp x8, x9\n"
        << "beq " << jumpLabel << "\n"; 
}
