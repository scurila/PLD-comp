#pragma once

#include <cinttypes>
#include "IR.h"


class IRInstr_pushconst : public IRInstr {

    public :

        IRInstr_pushconst(BasicBlock *bb_, int64_t value): IRInstr(bb_, pushconst, ""), value(value) {}

        void gen_x86(ostream &o) override; /** < x86 assembly code generation for this IR instruction */
	    void gen_arm(ostream &o) override; /** < M1 ARM assembly code generation for this IR instruction */

    private :

        int64_t value;
};


