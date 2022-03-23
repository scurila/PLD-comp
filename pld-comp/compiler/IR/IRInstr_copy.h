#include "IR.h"
#include <string>

class IRInstr_copy : public IRInstr {
    public:
        IRInstr_copy(BasicBlock *bb_, string d, string v) : IRInstr(bb_, copy, ""), dest(d), val(v) {};
        
        virtual void gen_x86(ostream &o); /** < x86 assembly code generation for this IR instruction */
        virtual void gen_arm(ostream &o); /** < M1 ARM assembly code generation for this IR instruction */

        // copy dest val ↔️ dest = val; 
        string dest;
        string val;
};
