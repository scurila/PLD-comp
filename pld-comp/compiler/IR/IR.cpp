#include "IR.h"

void IRInstr::gen_asm(ostream &o, bool x86) {/** ARM generation wrapper (calls x86 or arm generator based on flag) */
    if (x86) gen_x86(o);
    else gen_arm(o);
}
