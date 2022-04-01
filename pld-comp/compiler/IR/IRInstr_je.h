#pragma once

#include "IR.h"

class IRInstr_je : public IRInstr
{
public:
    IRInstr_je(BasicBlock *bb, std::string label) : IRInstr(bb, je, ""), jumpLabel(label) {}

    void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
    void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */

private:
    std::string jumpLabel;
};
