#pragma once

#include "IR.h"
#include <string>

class IRInstr_call : public IRInstr {
    public:
        IRInstr_call(BasicBlock *bb_, string funcname, int nbparam) : IRInstr(bb_, call, "") {
            nbparam=nbparam;
        };
        
        void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
        void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */

    private:
        int nbparam;
};