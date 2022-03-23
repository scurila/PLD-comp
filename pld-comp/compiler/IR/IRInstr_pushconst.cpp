#include "IRInstr_pushconst.h"


void IRInstr_pushconst::gen_x86(ostream &o) {

    o << "pushq $0x" << std::hex << value << std::dec << std::endl;// converted to hex to handle negative values (but grammar does not handle it so it is untested for now)
}

void IRInstr_pushconst::gen_arm(ostream &o) {
    o << "  mov w8 #" << value << std::endl; 
}
