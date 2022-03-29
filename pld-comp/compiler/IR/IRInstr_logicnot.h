#pragma once

#include "IR.h"

/** Used to get to logically negated value of variable: !var  (as opposed to bitwise not, ~var) */

class IRInstr_logicnot : public IRInstr
{
public:
    IRInstr_logicnot(BasicBlock *bb) : IRInstr(bb, popvar, "") {}

    void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
    void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */

private:
    Entry *variable;
};
