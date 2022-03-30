
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

}
