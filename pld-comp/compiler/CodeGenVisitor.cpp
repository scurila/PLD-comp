#include "CodeGenVisitor.h"
#include "IR/IRInstr_binand.h"
#include "IR/IRInstr_pushconst.h"
#include "Utils.h"
#include "Exceptions.h"
#include "IR/instr.h"
#include <cstdint>
#include <string>
#include <stack>

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
	funcCtxt.push(SymbolTable());
	antlrcpp::Any childrenRes = visitChildren(ctx);
	// verif stack de la fonction toutes vars utilisées - sinon warning
	vector<string> unusedVars = funcCtxt.top().unusedVars();
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

		
antlrcpp::Any CodeGenVisitor::visitReturnExpr(ifccParser::ReturnExprContext *context) 
{
	visit(context->children[1]); // visit expr

	// TODO ? for now, handling of returned value is made through the stack (last element pushed), and read in the epilogue

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitInitVarConst(ifccParser::InitVarConstContext *context)
{
	/*int cteVal = stoi(context->CONST()->getText());
	std::string literalName = context->LITERAL()->getText();

	try {
		funcCtxt.top().addEntry(literalName, context->type()->getText());
		std::cout
			<< "  movl $" << cteVal << ", " << (-1 * funcCtxt.top().get(literalName)->bp_offset) << "(%rbp)\n";
	} catch (DeclaredVarException e) {
		errorMessage(e.message());
		// todo : return différent ? 
	}
*/
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
			funcCtxt.top().addEntry(literalName, type);
			cfg->symbolTable->addEntry(literalName, type);

			cfg->current_bb->add_IRInstr(new IRInstr_ldconst(cfg->current_bb, literalName, value));

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
			funcCtxt.top().addEntry(literalName, type);
			cfg->symbolTable->addEntry(literalName, type);
		} catch (DeclaredVarException e) {
			errorMessage(e.message());
			// todo : return différent ? 
		}
	}	

	return 0;
}
/*
antlrcpp::Any CodeGenVisitor::visitLiterallist(ifccParser::LiterallistContext *context) 
{
	std::cout << "# literal list element\n";

	std::string literalName = context->LITERAL()->getText();
	
	funcCtxt.top().addEntry(literalName, currentChainedDeclarationType, typeSize(currentChainedDeclarationType));

	return visitChildren(context);
}*/

antlrcpp::Any CodeGenVisitor::visitAssignVar(ifccParser::AssignVarContext *context)
{

	
	string var1 = context->LITERAL()[0]->getText();
	string var2 = context->LITERAL()[1]->getText();

	try {
	    cfg->current_bb->add_IRInstr(new IRInstr_copy(cfg->current_bb, var1, var2));
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
		int index = funcCtxt.top().get(literal)->bp_offset;
		cfg->current_bb->add_IRInstr(new IRInstr_ldconst(cfg->current_bb, literal, stoi(context->CONST()->getText())));

	} catch (UndeclaredVarException e) {
		errorMessage(e.message());
	}
	return 0;
}


antlrcpp::Any CodeGenVisitor::visitAssignExpr(ifccParser::AssignExprContext *context) { 
	
	visit(context->children[2]); // explore expr

	std::string literal = context->LITERAL()->getText();

    cfg->current_bb->add_IRInstr(new IRInstr_popvar(cfg->current_bb, literal));

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
    	cfg->current_bb->add_IRInstr(new IRInstr_add(cfg->current_bb));
	}
	else if(op == "-") {
		cfg->current_bb->add_IRInstr(new IRInstr_sub(cfg->current_bb));
	}

	return 0; 
 }
/*
antlrcpp::Any CodeGenVisitor::visitOperatorSub(ifccParser::OperatorSubContext *context) {

	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack

	cfg->current_bb->add_IRInstr(new IRInstr_sub(cfg->current_bb));
    return 0;
}*/


antlrcpp::Any CodeGenVisitor::visitLiteralExpr(ifccParser::LiteralExprContext *context) {
	std::string literal = context->LITERAL()->getText();
	Entry *literalEntry = funcCtxt.top().get(literal);

    cfg->current_bb->add_IRInstr(new IRInstr_pushvar(cfg->current_bb,literal));

	return 0;
 }

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) 
{
	int64_t val = stoll(ctx->CONST()->getText());
	cfg->current_bb->add_IRInstr(new IRInstr_pushconst(cfg->current_bb, val));

    return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorMultDivMod(ifccParser::OperatorMultDivModContext *context) { 
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack 

	string op = context->children[1]->getText();

	if(op == "*") {
    	cfg->current_bb->add_IRInstr(new IRInstr_mul(cfg->current_bb));
	}
	else if(op == "/") {
		cfg->current_bb->add_IRInstr(new IRInstr_div(cfg->current_bb));
	}
	else if(op == "%") {
		cfg->current_bb->add_IRInstr(new IRInstr_mod(cfg->current_bb));
	}

	return 0;
}


/*antlrcpp::Any CodeGenVisitor::visitOperatorDiv(ifccParser::OperatorDivContext *context) { 

	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack

	cfg->current_bb->add_IRInstr(new IRInstr_div(cfg->current_bb));

	return 0;
}*/

antlrcpp::Any CodeGenVisitor::visitOperatorCmp(ifccParser::OperatorCmpContext *context) {
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack
	string op = context->children[1]->getText();

	if (op == "=="){
		cfg->current_bb->add_IRInstr(new IRInstr_cmpeq(cfg->current_bb));
	}
	else if (op == "<"){
		cfg->current_bb->add_IRInstr(new IRInstr_cmplt(cfg->current_bb));
	}
	else if (op == "<="){
		cfg->current_bb->add_IRInstr(new IRInstr_cmple(cfg->current_bb));
	}
	else if (op == ">"){
		cfg->current_bb->add_IRInstr(new IRInstr_cmpgt(cfg->current_bb));
	}
	else if (op == ">="){
		cfg->current_bb->add_IRInstr(new IRInstr_cmpge(cfg->current_bb));
	}
	else if (op == "!="){
		cfg->current_bb->add_IRInstr(new IRInstr_cmpineq(cfg->current_bb));
	}

    return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorUnaryPrefix(ifccParser::OperatorUnaryPrefixContext *context) {
	visit(context->children[1]);

	string op = context->children[0]->getText();

	if (op == "-") {
		cfg->current_bb->add_IRInstr(new IRInstr_opp(cfg->current_bb));
	}
	else if (op == "!") {
		cfg->current_bb->add_IRInstr(new IRInstr_logicnot(cfg->current_bb));
	}
	
	return 0;
}


antlrcpp::Any CodeGenVisitor::visitOperatorBinary(ifccParser::OperatorBinaryContext *context) {
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack
	string op = context->children[1]->getText();

	if (op == "&"){
		cfg->current_bb->add_IRInstr(new IRInstr_binand(cfg->current_bb));
	}
	else if (op == "|"){
		cfg->current_bb->add_IRInstr(new IRInstr_binor(cfg->current_bb));
	}

	return 0;
}


antlrcpp::Any CodeGenVisitor::visitCharExpr(ifccParser::CharExprContext *context) {
	std::string charac = context->CHAR()->getText();
	
	int64_t convert = (int64_t) charac[1];
	
    cfg->current_bb->add_IRInstr(new IRInstr_pushconst(cfg->current_bb,convert));
	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitCallFuncNoArgs(ifccParser::CallFuncNoArgsContext *context)  {
	std::string funcname = context->LITERAL()->getText();
	cfg->current_bb->add_IRInstr(new IRInstr_call(cfg->current_bb, funcname, 0));
    return 0;
}

  
antlrcpp::Any CodeGenVisitor::visitCallFuncArgs(ifccParser::CallFuncArgsContext *context) {
	//visit x children (x arguments, compter le nombre)
	//visit(context->children[0]);// pushes result in the stack 
	
	//cfg->current_bb->add_IRInstr(new IRInstr_call(cfg->current_bb, funcname, nbargs));

	return 0;
}


antlrcpp::Any CodeGenVisitor::visitIfElseIfElse(ifccParser::IfElseIfElseContext *context) {

	auto exprs = context->expr();
	auto instructions = context->instrblock();

	BasicBlock *original_block = cfg->current_bb;
	BasicBlock *end_block = new BasicBlock(cfg, cfg->new_bb_name());

	for(int i = 0; i < instructions.size(); i++) {
		auto instrCtx = instructions[i];
		if( i < exprs.size() ) { // means we're in a if (...) or else if (...)
			auto exprCtx = exprs[i];
			cfg->current_bb = original_block;
			visit(exprCtx);  // pushes boolean to the stack, result of evaluation
		}
		

		// Add new basic block for this branch
		auto bb = new BasicBlock(cfg, cfg->new_bb_name());
		cfg->add_bb(bb);

		// Generate branch code
		cfg->current_bb = bb;
		visit(instrCtx);

		// Add branching logic to starting block
		if ( i != exprs.size() ) {  // means we're reading an if or else if
			original_block->add_IRInstr( new IRInstr_pushconst(original_block, 0) );
			original_block->add_IRInstr( new IRInstr_jne(original_block, cfg->current_bb->label) );
		}
		else {  // means we're reading the else branch
			// inconditionally jump to else block, as it is the default option
			original_block->add_IRInstr( new IRInstr_jmp(original_block, cfg->current_bb->label) );
		}

		// jump to end block
		cfg->current_bb->add_IRInstr( new IRInstr_jmp(cfg->current_bb, end_block->label) );
	}

	cfg->add_bb(end_block);
	cfg->current_bb = end_block;

/*
	for(auto instrCtx : instructions) {
		visit(exprCtx);
		original_block->addIRInstr( push + jne )
	}

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<InstrblockContext *> instrblock();*/

	return 0;
}

/*

test              	| preceding code, leaves 0 or 1 on stack
cmp test != 0 ?   	| pushconst + IR_jne ? voir si adaptation de cmpineq possible ?
jne test_ok			|
test2				|
cmp test2 != 0 ?	|
jne test2_ok		|
test3				|
cmp test3 != 0 ?	|
jne test3			|
[else code here]	|
jmp endif			|

test_ok:
	jmp endif
test2_ok:
	jmp endif
test3_ok:
	jmp endif

endif:
	blabla





*/
