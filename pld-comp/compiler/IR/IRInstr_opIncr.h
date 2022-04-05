#pragma once

#include "IR.h"

class IRInstr_opIncr : public IRInstr {
    public:

            IRInstr_opIncr(BasicBlock *bb_): IRInstr(bb_, op_incr, ""){};

            void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
            void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */
    private:
};