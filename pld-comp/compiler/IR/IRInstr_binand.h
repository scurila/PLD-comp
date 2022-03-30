#pragma once

#include "IR.h"
#include <string>

class IRInstr_binand : public IRInstr {
    public:
        IRInstr_binand(BasicBlock *bb_, string l, string r, string d) : IRInstr(bb_, binand, ""), leftmember(l), rightmember(r), destination(d) {};
        
        void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
        void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */

        string leftmember;
        string right member;
        string destination;
};