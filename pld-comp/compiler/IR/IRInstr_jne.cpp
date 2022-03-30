
#include "IRInstr_jne.h"

void IRInstr_jne::gen_x86(ostream &o)
{
    o << "  popq %rax\n"
      << "  popq %rbx\n"
      << "  cmp %rax, %rbx\n"
      << "  jne " << jumpLabel << "\n";
}

void IRInstr_jne::gen_arm(ostream &o)
{

}
