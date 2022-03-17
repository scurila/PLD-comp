#pragma once

#include "IR.h"

class IRInstr_sub : IRInstr {

    public:
            IRInstr_sub(BasicBlock *bb_, Operation op, string t): IRInstr(BasicBlock *bb_, Operation op, string t){};

            virtual void gen_x86(ostream &o); /** < x86 assembly code generation for this IR instruction */
            virtual void gen_arm(ostream &o); /** < M1 ARM assembly code generation for this IR instruction */
}
