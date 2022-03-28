
#include "IRInstr_ldconst.h"
#include "../Utils.h"

void IRInstr_ldconst::gen_x86(ostream &o)
{
    std::string mov = makeInstrSuffix_x86("mov", variable->type);
    std::string ax = makeRegisterName_x86("ax", variable->type);

    size_t type_size = typeSize(variable->type);
    int64_t value_truncated = value;

    switch(type_size)
    {
        case 8:
            break;
        case 4:
            value_truncated &= 0xFFFFFFFF; 
            break;
        case 2:
            value_truncated &= 0xFFFF;
            break;
        case 1:
            value_truncated &= 0xFF;
            break;
    }

    o << "  " << mov << " $0x" << std::hex << value_truncated << std::dec << ", "<< -variable->bp_offset <<"(%rbp)\n";
}

void IRInstr_ldconst::gen_arm(ostream &o)
{  
    o << "; -- ldconst \n";
    o << "mov w8, #" << value << "\n"
    << "str w8, [sp, #" << variable->bp_offset << "]\n"; 
}
