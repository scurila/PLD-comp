#include "IR.h"

void IRInstr::gen_asm(ostream &o, Arch arch) {/** ARM generation wrapper (calls x86 or arm generator based on flag) */
    switch(arch) 
    {
        case x86:
            gen_x86(o);
            return;
        case arm:
            gen_arm(o);
            return;
    }
}


SymbolTable * const IRInstr::symbolTable() const
{
    return bb->cfg->symbolTable;
}




//CFG Methods :

void CFG::add_bb(BasicBlock *bb){
    bbs.push_back(bb);
}

void CFG::gen_asm(ostream &o, Arch arch){

    gen_prologue(o, arch);

    for( int i = 0; i < bbs.size(); i++){
        BasicBlock* b = bbs[i];
        o   << b->label
            <<":"
            << std::endl;

        b->gen_asm(o, arch);
    }

    gen_epilogue(o, arch);
}



void CFG::gen_prologue(ostream &o, Arch arch) {/** ARM generation wrapper (calls x86 or arm generator based on flag) */
    switch(arch)
    {
        case x86:
            gen_x86_prologue(o);
            return;
        case arm:
            gen_arm_prologue(o);
            return;
    }
}


void CFG::gen_epilogue(ostream &o, Arch arch) {/** ARM generation wrapper (calls x86 or arm generator based on flag) */
    switch(arch)
    {
        case x86:
            gen_x86_epilogue(o);
            return;
        case arm:
            gen_arm_epilogue(o);
            return;
    }
}


void CFG::gen_x86_prologue(ostream &o){
    #ifdef APPLE
        o   << ".globl _" << functionName << "\n"
    	    << "_" << functionName << ": \n";
    #else
    	o   << ".globl " << functionName << "\n"
            << functionName << ": \n";
    #endif
    o   << "  pushq %rbp\n"
        << "  pushq %rsi\n"
        << "  pushq %rdi\n"
        << "  pushq %rbx\n"
        << "  movq %rsp, %rbp\n";

    int alignedTopOffset = symbolTable->topOffset +  (8 - (symbolTable->topOffset % 8));

    	// TODO: temporary as we need to know the number of variables allocated (this needs IR set up, or a pre-run on the code to identify variables)
    o   << "  movq %rsp, %rax\n"
    	<< "  subq $" << alignedTopOffset << ", %rax\n"
    	<< "  movq %rax, %rsp\n";

}

void CFG::gen_x86_epilogue(ostream &o){
    o  << get_epilogue_label(x86) << ":\n";

    int alignedTopOffset = symbolTable->topOffset +  (8 - (symbolTable->topOffset % 8));

	o   // move rsp to pop rbp later
		<< "  movq %rsp, %rbx\n"
		<< "  addq $" << alignedTopOffset << ", %rbx\n"
		<< "  movq %rbx, %rsp\n";

	o  // restore rsp (and remove rbp from stack)
		<< "  popq %rbx\n"
        << "  popq %rdi\n"
        << "  popq %rsi\n"
        << "  popq %rbp\n"
		<< "  ret\n";
}

void CFG::gen_arm_prologue(ostream &o){
    int alignedTopOffset = symbolTable->topOffset +  (16 - (symbolTable->topOffset % 16));
    
    o   << ".globl	_" << functionName << "                           ; -- Begin function " << functionName << "\n"
        << ".p2align	3\n"
        << "_" << functionName << ":                                  ; @" << functionName << "\n"
        << ".cfi_startproc\n"
        << "; %bb.0:\n"
        // TODO: temporary as we need to know the number of variables allocated (this needs IR set up, or a pre-run on the code to identify variables)
        << "sub	sp, sp, #" << alignedTopOffset + 16 << "\n" // 16 for the x29 x30 backup, will be obfuscated by x29 
        << "stp x29, x30, [sp, #" << alignedTopOffset << "]\n" // (! pas compter les 16 pour écrire dans les 16 derniers) on stocke frame pointer & return pointer en base de la pile (16 oct) ==  16-byte folded spill
        << "add x29, sp, #" << alignedTopOffset << "\n" // on place le rbp en bas pile (mais au dessus des 2 backups à ne pas écraser - d'où pas le +16)
        << ".cfi_def_cfa_offset " << alignedTopOffset + 16 << "\n";
        // todo : change when functions supported
}

void CFG::gen_arm_epilogue(ostream &o){
    int alignedTopOffset = symbolTable->topOffset +  (16 - (symbolTable->topOffset % 16));
    
    o  << get_epilogue_label(arm) << ":\n";
	o
        << "ldp x29, x30, [sp, #" << alignedTopOffset << "]\n" // restaure x29 x30 (pas le +16 - les 16 derniers oct) == 16-byte folded reload
		<< "add sp, sp, #" << alignedTopOffset + 16 << "\n" // + les 16 de la backup 
		<< "ret\n"
		<< ".cfi_endproc\n"
        << ".subsections_via_symbols\n";
}

string CFG::get_epilogue_label(Arch arch) {
    return  "." + functionName + "_epilogue";
}

void CFG::add_to_symbol_table(string name, string type){
    symbolTable->addEntry(name, type);
}


string CFG::create_new_tempvar(string type){
    string tmpName = "tmp"+std::to_string(nbTmpVar);
    symbolTable->addEntry(tmpName, type);
    nbTmpVar++;
    return tmpName;
}

/*int CFG::get_var_index(string name){

}*/


string CFG::get_var_type(string name){
     return symbolTable->get(name)->type;

}

// basic block management
string CFG::new_bb_name(){
    string name = "L" + functionName + std::to_string(nextBBnumber);
    nextBBnumber++;
    return name;
}


// BasicBlock methods :

void BasicBlock::gen_asm(ostream &o, Arch arch)
{
    for( int i = 0; i < instrs.size(); i++){
        IRInstr* instr = instrs[i];
        instr->gen_asm(o, arch);
    }

    if(default_next_block) {
        if(arch == x86) {
            o << "  jmp " << default_next_block->label << "\n";
        }
        else if (arch == arm) {
            o << "  bl " << default_next_block->label << "\n";
        }
    }
    else {
        if(arch == x86) {
            o << "  jmp " << cfg->get_epilogue_label(arch) << "\n";
        }
        else if (arch == arm) {
            o << "  bl " << cfg->get_epilogue_label(arch) << "\n";
        }
    }
}

void BasicBlock::add_IRInstr(IRInstr *instr)
{
    instrs.push_back(instr);
}

