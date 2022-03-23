#include "IRInstr_comple.h"

void IRInstr_cmple::gen_x86(ostream &o) {

}

void IRInstr_cmple::gen_arm(ostream &o) {
    o << "; -- cmple \n";
    o << "pop {w8}\n" // right member
        << "pop {w9}\n" // left member 
        << "subs w9, w9, w8\n"
        << "cset w9, le\n"
        << "and w9, w9, #0x1\n" 
        << "push {w9}\n";
}
