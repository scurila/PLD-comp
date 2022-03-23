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


void CFG::gen_x86_prologue(ostream &o){
    o << ".text\n";
    #ifdef APPLE
        o   << ".globl _main\n"
    	    << "_main: \n";
    #else
    	o   << ".globl main\n"
    					<< "main: \n";
    # endif
    o   << "  pushq %rbp\n"
        << "  movq %rsp, %rbp\n";

    	// TODO: temporary as we need to know the number of variables allocated (this needs IR set up, or a pre-run on the code to identify variables)
    o   << "  movq %rsp, %rax\n"
    	<< "  subq $0x100, %rax\n"
    	<< "  movq %rax, %rsp\n";

}

void CFG::gen_x86_epilogue(ostream &o){
	o   // move rsp to pop rbp later
		<< "  movq %rsp, %rbx\n"
		<< "  addq $0x100, %rbx\n"
		<< "  movq %rbx, %rsp\n";

	o  // restore rsp (and remove rbp from stack)
		<< "  popq %rbp\n"
		<< "  ret\n";
}

void CFG::add_to_symbol_table(string name, string type){
    symbolTable->addEntry(name, type);
}


string CFG::create_new_tempvar(string type){
    string tmpName = "tmp"+std::to_string(nbTmpVar);
    symbolTable->addEntry(tmpName, type);
    return tmpName;
}

/*int CFG::get_var_index(string name){

}*/


string CFG::get_var_type(string name){
     return symbolTable->get(name)->type;

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

