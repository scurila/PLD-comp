#pragma once

#include "IR.h"

class IRInstr_jne : public IRInstr
{
public:
    IRInstr_jne(BasicBlock *bb, std::string label) : IRInstr(bb, jne, ""), jumpLabel(label) {}

    void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
    void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */

private:
    std::string jumpLabel;
};
