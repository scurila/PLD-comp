#pragma once

#include "IR.h"

class IRInstr_div : IRInstr {
    public:
            IRInstr_div(BasicBlock *bb_): IRInstr(bb_, div, ""){};

            virtual void gen_x86(ostream &o); /** < x86 assembly code generation for this IR instruction */
            virtual void gen_arm(ostream &o); /** < M1 ARM assembly code generation for this IR instruction */
};
