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

    for( int i = 0; i < bbs.size(); i++){
        BasicBlock* b = bbs[i];
        o   << b->label
            <<":"
            << std::endl;

        b->gen_asm(o, arch);
    }
}



void IRInstr::gen_prologue(ostream &o, Arch arch) {/** ARM generation wrapper (calls x86 or arm generator based on flag) */
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

void CFG::gen_x86_prologue(ostream &o){
    o << ".text\n";
    #ifdef APPLE
        o   << ".globl _main\n"
    	    << "_main: \n";
    #else
    	o   << ".globl main\n"
    					<< "main: \n";
    #endif
    o   << "  pushq %rbp\n"
        << "  movq %rsp, %rbp\n";

    	// TODO: temporary as we need to know the number of variables allocated (this needs IR set up, or a pre-run on the code to identify variables)
    o   << "  movq %rsp, %rax\n"
    	<< "  subq $0x100, %rax\n"
    	<< "  movq %rax, %rsp\n";

}

void CFG::gen_x86_epilogue(ostream &o){
    o  << "  popq %rax\n";  // pop returned value to rax

	o   // move rsp to pop rbp later
		<< "  movq %rsp, %rbx\n"
		<< "  addq $0x100, %rbx\n"
		<< "  movq %rbx, %rsp\n";

	o  // restore rsp (and remove rbp from stack)
		<< "  popq %rbp\n"
		<< "  ret\n";
}

void CFG::gen_arm_prologue(ostream &o){
    o << ".section	__TEXT,__text,regular,pure_instructions\n";
    o   << ".build_version macos, 12, 0	sdk_version 12, 3\n"
        << ".globl	_main                           ; -- Begin function main\n"
        << ".p2align	2\n"
        << "_main:                                  ; @main\n"
        << ".cfi_startproc\n"
        << "; %bb.0:\n"
        // TODO: temporary as we need to know the number of variables allocated (this needs IR set up, or a pre-run on the code to identify variables)
        << "sub	sp, sp, #100\n"
        << ".cfi_def_cfa_offset 100\n";
        // todo : change when functions supported
}

void CFG::gen_arm_epilogue(ostream &o){
	o
    // todo : 100 temp
		<< "  add     sp, sp, #100\n"
		<< "  ret\n"
		<< "  .cfi_endproc\n"
        << "  .subsections_via_symbols\n";
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
string CFG::new_BB_name(){
    string name = ".L"+std::to_string(nextBBnumber);
    nextBBnumber++;//est-ce qu'on le fait ici ??
    return name;
}


// BasicBlock methods :

void BasicBlock::gen_asm(ostream &o, Arch arch)
{
    for( int i = 0; i < instrs.size(); i++){
        IRInstr* instr = instrs[i];
        instr->gen_asm(o, arch);
    }
}

void BasicBlock::add_IRInstr(IRInstr *instr)
{
    instrs.push_back(instr);
}

