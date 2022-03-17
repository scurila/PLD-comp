#pragma once

#include <cinttypes>
#include "IR.h"


class IRInstr_pushconst : public IRInstr {

    public :

        IRInstr_pushconst(BasicBlock *bb_, int64_t value): IRInstr(bb_, pushconst, ""), value(value) {}

        virtual void gen_x86(ostream &o); /** < x86 assembly code generation for this IR instruction */
	    virtual void gen_arm(ostream &o); /** < M1 ARM assembly code generation for this IR instruction */

    private :

        int64_t value;
};


