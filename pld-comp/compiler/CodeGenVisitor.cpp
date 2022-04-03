#include "CodeGenVisitor.h"
#include "IR/IRInstr_binand.h"
#include "IR/IRInstr_pushconst.h"
#include "Utils.h"
#include "Exceptions.h"
#include "IR/instr.h"
#include <cstdint>
#include <string>
#include <stack>

antlrcpp::Any CodeGenVisitor::visitMain(ifccParser::MainContext *ctx) 
{
	CFG *main_cfg = new CFG("main");
	program->add_cfg(main_cfg);
	set_cfg(main_cfg);

	antlrcpp::Any childrenRes = visitChildren(ctx);
	// verif stack de la fonction toutes vars utilisées - sinon warning
	vector<string> unusedVars = cur_cfg()->symbolTable->unusedVars();
	if (!unusedVars.empty()) {
		string msg = "Dans ce contexte, la ou les variables suivantes on été déclarées mais n'ont pas été utilisées : ";
		for (vector<string>::iterator it=unusedVars.begin(); it!=unusedVars.end(); ++it) {
			msg.append(*it);
			if ((it+1) != unusedVars.end()) msg.append(", ");
		}
		warningMessage(msg);
	}

	return childrenRes;
}

antlrcpp::Any CodeGenVisitor::visitInstrblock(ifccParser::InstrblockContext *context) 
{
	cur_cfg()->symbolTable->push_context(); // push new inner scope

	auto childrenRes = visitChildren(context);

	cur_cfg()->symbolTable->pop_context(); // leave inner scope

	return childrenRes;
}
		
antlrcpp::Any CodeGenVisitor::visitReturnExpr(ifccParser::ReturnExprContext *context) 
{
	visit(context->children[1]); // visit expr

	cur_cfg()->current_bb->add_IRInstr(new IRInstr_return(cur_cfg()->current_bb, true));

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitReturnVoid(ifccParser::ReturnVoidContext *ctx)
{
	cur_cfg()->current_bb->add_IRInstr(new IRInstr_return(cur_cfg()->current_bb, false));

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitInitVarConst(ifccParser::InitVarConstContext *context)
{
	std::string type = context->type()->getText();
	int type_size = typeSize(type);
	uint64_t type_mask = 0;   // mask of ones of the length of type_size*8, used to check value length
	for(int i = 0; i < type_size * 8; i++) {
		type_mask |= ((uint64_t)1) << i;
	}

	auto literals = context->LITERAL();
	auto values = context->CONST();
	
	auto valuesIt = begin(values);
	for(auto itLit = begin(literals); itLit != end(literals); ++itLit) {
    	string literalName = (*itLit)->getText();
		int64_t value = stoll( (*valuesIt)->getText() );

		if((value & type_mask) != value) {
			std::ostringstream stream;
			stream << "Value " << value << " is too large to be stored in variable '" << literalName << "' (type " << type << "). Actual value will be truncated to " << (value & type_mask) << "."; 
			warningMessage(stream.str());
		}
		
		try {
			cur_cfg()->symbolTable->addEntry(literalName, type);
			cur_cfg()->current_bb->add_IRInstr(new IRInstr_ldconst(cur_cfg()->current_bb, literalName, value));
		} catch (DeclaredVarException e) {
			errorMessage(e.message());
			// todo : return différent ? 
		}
		++valuesIt;
	}	

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitDeclareVar(ifccParser::DeclareVarContext *context) 
{
	std::string type = context->type()->getText();
	auto literals = context->LITERAL();
	for(auto it = begin(literals); it != end(literals); ++it) {
    	string literalName = (*it)->getText();
		try {
			cur_cfg()->symbolTable->addEntry(literalName, type);
		} catch (DeclaredVarException e) {
			errorMessage(e.message());
			// todo : return différent ? 
		}
	}	

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignVar(ifccParser::AssignVarContext *context)
{
	string var1 = context->LITERAL()[0]->getText();
	string var2 = context->LITERAL()[1]->getText();

	try {
	    cur_cfg()->current_bb->add_IRInstr(new IRInstr_copy(cur_cfg()->current_bb, var1, var2));
	} catch (UndeclaredVarException e) {
		errorMessage(e.message());
		// todo : return différent ? 
	}
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignConst(ifccParser::AssignConstContext *context)
{
	
	try {
		std::string literal = context->LITERAL()->getText();
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_ldconst(cur_cfg()->current_bb, literal, stoi(context->CONST()->getText())));
	} catch (UndeclaredVarException e) {
		errorMessage(e.message());
	}
	return 0;
}


antlrcpp::Any CodeGenVisitor::visitAssignExpr(ifccParser::AssignExprContext *context) { 
	
	visit(context->children[2]); // explore expr

	std::string literal = context->LITERAL()->getText();

    cur_cfg()->current_bb->add_IRInstr(new IRInstr_popvar(cur_cfg()->current_bb, literal));

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorPar(ifccParser::OperatorParContext *context) {
	return visitChildren(context);
}

antlrcpp::Any CodeGenVisitor::visitOperatorAddSub(ifccParser::OperatorAddSubContext *context) {
	
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack 

	string op = context->children[1]->getText();

	if(op == "+") {
    	cur_cfg()->current_bb->add_IRInstr(new IRInstr_add(cur_cfg()->current_bb));
	}
	else if(op == "-") {
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_sub(cur_cfg()->current_bb));
	}

	return 0; 
}

antlrcpp::Any CodeGenVisitor::visitLiteralExpr(ifccParser::LiteralExprContext *context) {
	std::string literal = context->LITERAL()->getText();

    cur_cfg()->current_bb->add_IRInstr(new IRInstr_pushvar(cur_cfg()->current_bb,literal));

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) 
{
	int64_t val = stoll(ctx->CONST()->getText());
	cur_cfg()->current_bb->add_IRInstr(new IRInstr_pushconst(cur_cfg()->current_bb, val));

    return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorMultDivMod(ifccParser::OperatorMultDivModContext *context) { 
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack 

	string op = context->children[1]->getText();

	if(op == "*") {
    	cur_cfg()->current_bb->add_IRInstr(new IRInstr_mul(cur_cfg()->current_bb));
	}
	else if(op == "/") {
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_div(cur_cfg()->current_bb));
	}
	else if(op == "%") {
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_mod(cur_cfg()->current_bb));
	}

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorCmp(ifccParser::OperatorCmpContext *context) {
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack
	string op = context->children[1]->getText();

	if (op == "=="){
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_cmpeq(cur_cfg()->current_bb));
	}
	else if (op == "<"){
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_cmplt(cur_cfg()->current_bb));
	}
	else if (op == "<="){
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_cmple(cur_cfg()->current_bb));
	}
	else if (op == ">"){
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_cmpgt(cur_cfg()->current_bb));
	}
	else if (op == ">="){
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_cmpge(cur_cfg()->current_bb));
	}
	else if (op == "!="){
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_cmpineq(cur_cfg()->current_bb));
	}

    return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorUnaryPrefix(ifccParser::OperatorUnaryPrefixContext *context) {
	visit(context->children[1]);

	string op = context->children[0]->getText();

	if (op == "-") {
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_opp(cur_cfg()->current_bb));
	}
	else if (op == "!") {
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_logicnot(cur_cfg()->current_bb));
	}
	
	return 0;
}


antlrcpp::Any CodeGenVisitor::visitOperatorBinary(ifccParser::OperatorBinaryContext *context) {
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack
	string op = context->children[1]->getText();

	if (op == "&"){
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_binand(cur_cfg()->current_bb));
	}
	else if (op == "|"){
		cur_cfg()->current_bb->add_IRInstr(new IRInstr_binor(cur_cfg()->current_bb));
	}

	return 0;
}


antlrcpp::Any CodeGenVisitor::visitCharExpr(ifccParser::CharExprContext *context) {
	std::string charac = context->CHAR()->getText();
	
	int64_t convert = (int64_t) charac[1];
	
    cur_cfg()->current_bb->add_IRInstr(new IRInstr_pushconst(cur_cfg()->current_bb,convert));
	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitCallFuncNoArgs(ifccParser::CallFuncNoArgsContext *context)  {
	std::string funcname = context->LITERAL()->getText();
	cur_cfg()->current_bb->add_IRInstr(new IRInstr_call(cur_cfg()->current_bb, funcname, 0));
    return 0;
}

  
antlrcpp::Any CodeGenVisitor::visitCallFuncArgs(ifccParser::CallFuncArgsContext *context) {
	//visit x children (x arguments, compter le nombre)
	//visit(context->children[0]);// pushes result in the stack 
	//int nbargs= ??
	//std::string funcname = context->LITERAL()->getText();
	//cur_cfg()->current_bb->add_IRInstr(new IRInstr_call(cur_cfg()->current_bb, funcname, nbargs));

	return 0;
}


antlrcpp::Any CodeGenVisitor::visitIfElseIfElse(ifccParser::IfElseIfElseContext *context) {

	auto exprs = context->expr();  // list of expressions (might be size of instructions list - 1, because there can be an 'else' block)
	auto instructions = context->instrblock();  // list of instruction blocks

	BasicBlock *original_block = cur_cfg()->current_bb;  // block from which we're branching
	BasicBlock *end_block = new BasicBlock(cur_cfg(), cur_cfg()->new_bb_name()); // block in which the instruction flow will continue (all branches points to it)

	bool else_block = false;  // used to determine if the original_block needs to branch to an else block or to the end_block

	for(int i = 0; i < instructions.size(); i++) {
		auto instrCtx = instructions[i];
		if( i < exprs.size() ) { // means we're in a if (...) or else if (...)
			auto exprCtx = exprs[i];
			cur_cfg()->current_bb = original_block;
			visit(exprCtx);  // pushes boolean to the stack, result of evaluation
		}
		

		// Add new basic block for this branch
		auto bb = new BasicBlock(cur_cfg(), cur_cfg()->new_bb_name());
		bb->default_next_block = end_block; // will generate a jump to end_block at the end of this block
		cur_cfg()->add_bb(bb);

		// Generate branch code
		cur_cfg()->current_bb = bb;
		visit(instrCtx);

		// Add branching logic to starting block
		if ( i != exprs.size() ) {  // means we're reading an if or else if
			original_block->add_IRInstr( new IRInstr_pushconst(original_block, 0) );
			original_block->add_IRInstr( new IRInstr_jne(original_block, cur_cfg()->current_bb->label) );
		}
		else {  // means we're reading the else branch
			// inconditionally jump to else block, as it is the default option
			original_block->default_next_block = cur_cfg()->current_bb;
			else_block = true;
		}
	}

	if(!else_block) { // means we need to branch directly to end_block at the end of original_block
		original_block->default_next_block = end_block;
	}

	cur_cfg()->add_bb(end_block);
	cur_cfg()->current_bb = end_block;

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitWhileLoop(ifccParser::WhileLoopContext *context) {

	auto expr = context->expr();
	auto instructions = context->instrblock();

	BasicBlock *original_block = cur_cfg()->current_bb;  // block from which we're branching
	
	BasicBlock *while_start = new BasicBlock(cur_cfg(), cur_cfg()->new_bb_name()); // block for while condition check and instructions
	BasicBlock *end_block = new BasicBlock(cur_cfg(), cur_cfg()->new_bb_name()); // block to jump to when while condition does not check anymore

	original_block->default_next_block = while_start; // connect previous intruction flow with start of while
	while_start->default_next_block = while_start; // should jump to itself to loop
	
	// begin while code
	cur_cfg()->current_bb = while_start;

	// while condition evaluation
	visit(expr); 

	// check condition ; if evaluation returned 0, jump to end_block
	while_start->add_IRInstr( new IRInstr_pushconst(while_start, 0) );
	while_start->add_IRInstr( new IRInstr_je(while_start, end_block->label) );

	// add while body after condition check
	visit(instructions);

	// loop jump will be generated automatically, as we set default_next_block

	cur_cfg()->add_bb(while_start);
	cur_cfg()->add_bb(end_block);

	cur_cfg()->current_bb = end_block;

	return 0;
	/*

		while_begin:
			test
			cmp res, $0
			je while_end   # condition is false, leave

			while_body
			{
				if meets continue in instrbody:
					jmp 
			}

			jmp while_begin
		
		while_end:
			continue with normal code


	*/
}
