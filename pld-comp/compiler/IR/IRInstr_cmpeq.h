#pragma once

#include "IR.h"
#include <string>

class IRInstr_cmpeq : public IRInstr {
    public:
        IRInstr_cmpeq(BasicBlock *bb_) : IRInstr(bb_,cmp_eq, "") {};
        
        void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
        void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */
};
