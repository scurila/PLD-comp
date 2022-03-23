#pragma once

#include "IR.h"

class IRInstr_pushvar : public IRInstr
{
public:
    IRInstr_pushvar(BasicBlock *bb, std::string variableName) : IRInstr(bb, pushvar, "") {
        variable = symbolTable()->get(variableName);
        type = variable->type;
    }

    void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
    void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */

private:
    Entry *variable;
};
