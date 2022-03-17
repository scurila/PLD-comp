#include "IR.h"
#include <string>

class IRInstr_add : IRInstr {
    public:
        IRInstr_add(BasicBlock *bb_, Operation op, Type t, string v1, string v2, string v3) : IRInstr(BasicBlock *bb_, Operation op, Type t), var1(v1), var2(v2), var3(v3) {} ;

        // add var1 var2 var3 ≣ var1 = var2 + var3
        string var1, var2, var3; 
}
