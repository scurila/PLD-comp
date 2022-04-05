
#include "IRInstr_logicnot.h"
#include "../Utils.h"

void IRInstr_logicnot::gen_x86(ostream &o)
{
    o << "  popq %rax\n"
      << "  cmpq $0, %rax\n"
      << "  sete %al\n"
      << "  movzbq %al, %rax\n"
      << "  pushq %rax\n";
}

void IRInstr_logicnot::gen_arm(ostream &o)
{
    o << "; -- not \n";
    o << "ldr x8, [sp], #16\n" // POP right member
        << "mvn x8, x8\n"
        << "str x8, [sp, #-16]!\n"; // push w8 
}

