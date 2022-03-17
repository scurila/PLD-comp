#include "IR.h"
#include <string>

class IRInstr_add : IRInstr {
    public:
        IRInstr_add(BasicBlock *bb_, Operation op, Type t, string v1, string v2, string v3) : IRInstr(BasicBlock *bb_, Operation op, Type t) {} ;

        virtual void gen_x86(ostream &o); /** < x86 assembly code generation for this IR instruction */
	    virtual void gen_arm(ostream &o); /** < M1 ARM assembly code generation for this IR instruction */
}
