#pragma once

#include "IR.h"
#include <string>

class IRInstr_cmpgt : public IRInstr {
    public:
        IRInstr_cmpgt(BasicBlock *bb_) : IRInstr(bb_,cmp_gt, "") {};
        
        void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
        void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */
};
