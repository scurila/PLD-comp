#pragma once

#include "IR.h"

class IRInstr_return : public IRInstr
{
public:
    IRInstr_return(BasicBlock *bb, bool hasValue) : IRInstr(bb, jmp, ""), hasValue(hasValue) {}

    void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
    void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */

private:
    bool hasValue;
};
