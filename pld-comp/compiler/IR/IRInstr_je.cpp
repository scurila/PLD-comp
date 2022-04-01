
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

}
