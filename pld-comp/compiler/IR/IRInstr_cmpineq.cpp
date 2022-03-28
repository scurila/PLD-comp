#include "IRInstr_cmpineq.h"

void IRInstr_cmpineq::gen_x86(ostream &o) {
    o   << "# cmpineq\n";

    o   <<	"  popq %rbx\n"//right member
        << "  popq %rax\n"//left member
        << "  cmp %rbx, %rax\n"//compare content of a and b
        << "  setnz %rax\n"
        << "  pushq %rax\n";
}

void IRInstr_cmpineq::gen_arm(ostream &o) {

}
