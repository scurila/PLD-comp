#pragma once

#include "IR.h"

class IRInstr_pushvar : IRInstr
{
public:
    IRInstr_pushvar(BasicBlock *bb, std::string variableName) : IRInstr(bb, pushvar, "") {
        variable = symbolTable()->get(variableName);
        type = variable->type;
    }

    virtual void gen_x86(ostream &o); /** < x86 assembly code generation for this IR instruction */
    virtual void gen_arm(ostream &o); /** < M1 ARM assembly code generation for this IR instruction */

private:
    Entry *variable;
};
