#include "CodeGenVisitor.h"
#include "Utils.h"
#include "Exceptions.h"
#include "IR/instr.h"
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


	std::cout << "IR generated code below!" << std::endl;

	cfg->gen_x86_prologue(std::cout);
	cfg->gen_asm(std::cout, x86);
	cfg->gen_x86_epilogue(std::cout);

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
	
	std::cout << "# init var\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitDeclareVar(ifccParser::DeclareVarContext *context) 
{
	std::string type = context->type()->getText();
	std::vector<antlr4::tree::TerminalNode *> literals = context->LITERAL();
	for(std::vector<antlr4::tree::TerminalNode *>::iterator it = begin(literals); it != end(literals); ++it) {
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

antlrcpp::Any CodeGenVisitor::visitOperatorSub(ifccParser::OperatorSubContext *context) {

	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack

	cfg->current_bb->add_IRInstr(new IRInstr_sub(cfg->current_bb));
    return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorPar(ifccParser::OperatorParContext *context) {
	return visitChildren(context);
}

antlrcpp::Any CodeGenVisitor::visitOperatorDiv(ifccParser::OperatorDivContext *context) { 

	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack

	cfg->current_bb->add_IRInstr(new IRInstr_div(cfg->current_bb));

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorAdd(ifccParser::OperatorAddContext *context) {
	
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack 
    cfg->current_bb->add_IRInstr(new IRInstr_add(cfg->current_bb));

	return 0; 
 }

antlrcpp::Any CodeGenVisitor::visitLiteralExpr(ifccParser::LiteralExprContext *context) {
	std::string literal = context->LITERAL()->getText();
	Entry *literalEntry = funcCtxt.top().get(literal);

    cfg->current_bb->add_IRInstr(new IRInstr_pushvar(cfg->current_bb,literal));

	return 0;
 }

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) 
{
	int val = stoi(ctx->CONST()->getText());
	cfg->current_bb->add_IRInstr(new IRInstr_pushconst(cfg->current_bb, val));

    return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorMult(ifccParser::OperatorMultContext *context) { 
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack 

    cfg->current_bb->add_IRInstr(new IRInstr_mul(cfg->current_bb));

	return 0;
}
