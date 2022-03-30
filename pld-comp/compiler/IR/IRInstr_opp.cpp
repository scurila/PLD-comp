
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

}
