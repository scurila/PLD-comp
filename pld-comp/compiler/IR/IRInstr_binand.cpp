
#include "IRInstr_binand.h"
#include "../Utils.h"

void IRInstr_binand::gen_x86(ostream &o) {
    o << "# binary_and\n";

    o 
        << "  movl "<< -1* symbolTable()->get(leftmem)->bp_offset <<"(%rbp), " << "%eax\n";
    o
        << "  andl "<< -1* symbolTable()->get(rightmem)->bp_offset <<"(%rbp), " << "%eax\n";
    o
        << "  movl "<< "%eax, " << -1* symbolTable()->get(dest)->bp_offset <<"(%rbp)\n";

}

void IRInstr_binand::gen_arm(ostream &o) {
    
}
