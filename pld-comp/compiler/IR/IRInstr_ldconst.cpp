
#include "IRInstr_ldconst.h"
#include "../Utils.h"

void IRInstr_ldconst::gen_x86(ostream &o)
{
    std::string mov = makeInstrSuffix_x86("mov", variable->type);
    std::string bp = makeRegisterName_x86("bp", variable->type);
    std::string ax = makeRegisterName_x86("ax", variable->type);

    size_t type_size = typeSize(variable->type);

    switch(type_size)
    {
        case 8:
            o << "  " << mov << " $0x" << std::hex << value << std::dec << ", "<< -variable->bp_offset <<"(" << bp << ")\n";
            break;
        case 4:
            o << "  " << mov << " $0x" << std::hex << (int32_t)(value & 0xFFFFFFFF) << std::dec << ", "<< -variable->bp_offset <<"(" << bp << ")\n";
            break;
        case 2:
            o << "  " << mov << " $0x" << std::hex << (int16_t)(value & 0xFFFF) << std::dec << ", "<< -variable->bp_offset <<"(" << bp << ")\n";
            break;
        case 1:
            o << "  " << mov << " $0x" << std::hex << (int8_t)(value & 0xFF) << std::dec << ", "<< -variable->bp_offset <<"(" << bp << ")\n";
            break;
    }
}

void IRInstr_ldconst::gen_arm(ostream &o)
{

}
