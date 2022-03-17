#pragma once

#include "IR.h"

class IRInstr_add : IRInstr {
    public:
        IRInstr_add(BasicBlock *bb_, Operation op, Type t, vector<string> params) : IRInstr(BasicBlock *bb_, Operation op, Type t, vector<string> params);
        
        virtual void gen_x86(ostream &o); /** < x86 assembly code generation for this IR instruction */
        virtual void gen_arm(ostream &o); /** < M1 ARM assembly code generation for this IR instruction */

    private:

}
