#pragma once

#include "IR.h"
#include <string>

class IRInstr_add : public IRInstr {
    public:
        IRInstr_add(BasicBlock *bb_) : IRInstr(bb_, add, "") {};
        
        virtual void gen_x86(ostream &o); /** < x86 assembly code generation for this IR instruction */
        virtual void gen_arm(ostream &o); /** < M1 ARM assembly code generation for this IR instruction */
};
