#pragma once

#include "IR.h"

class IRInstr_mul : public IRInstr {
    public:

            IRInstr_mul(BasicBlock *bb_): IRInstr(bb_, mul, ""){};

            virtual void gen_x86(ostream &o); /** < x86 assembly code generation for this IR instruction */
            virtual void gen_arm(ostream &o); /** < M1 ARM assembly code generation for this IR instruction */
    private:
};
