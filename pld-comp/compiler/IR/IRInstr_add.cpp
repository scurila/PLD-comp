#include "IRInstr_add.h"

void IRInstr_add::gen_x86(ostream &o) {
    o << "# add\n";
    o << "  popq %rbx\n"//right member
      << "  popq %rax\n"//left member
      << "  add %rbx, %rax\n"// add a and b and stores result in a
      << "  pushq %rax\n";*/
}

void IRInstr_add::gen_arm(ostream &o) {

}
