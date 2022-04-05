#pragma once

#include "IR.h"

class IRInstr_call : public IRInstr {
    public:
        IRInstr_call(BasicBlock *bb_, std::string funcname, int nbparam) : IRInstr(bb_, call, ""), nbParams(nbparam), functionName(funcname) {};
        
        void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
        void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */

    private:
        int nbParams;
        std::string functionName;
};