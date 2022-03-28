#pragma once

#include "IR.h"
#include <string>

class IRInstr_cmple : public IRInstr {
    public:
        IRInstr_cmple(BasicBlock *bb_) : IRInstr(bb_, cmp_le, "") {};
        
        void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
        void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */
};
