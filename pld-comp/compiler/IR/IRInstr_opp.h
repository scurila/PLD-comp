#pragma once

#include "IR.h"

/** Used to get the opposite of a number */

class IRInstr_opp : public IRInstr
{
public:
    IRInstr_opp(BasicBlock *bb, std::string variableName) : IRInstr(bb, popvar, "") {
        variable = symbolTable()->get(variableName);
        type = variable->type;
    }

    void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
    void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */

private:
    Entry *variable;
};
