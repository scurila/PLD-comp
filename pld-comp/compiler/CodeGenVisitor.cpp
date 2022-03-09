#include "CodeGenVisitor.h"
#include <string>
#include <stack>



antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
	std::cout << ".text\n"
	          << ".globl main\n"
			  << "main: \n" 
			  << "  pushq %rbp\n"
			  << "  movq %rsp, %rbp\n";

	funcCtxt.push(SymbolTable());
	return visitChildren(ctx);
}

		
antlrcpp::Any CodeGenVisitor::visitReturnExpr(ifccParser::ReturnExprContext *context) 
{ 
	int retval = stoi(context->CONST()->getText());
	std::cout 
			<< "  movl $" << retval << ", %eax\n"
			<< "  popq %rbp\n"
	 		<< "  ret\n";

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitInitVarConst(ifccParser::InitVarConstContext *context)
{
	int cteVal = stoi(context->CONST()->getText());
	std::string literalName = context->LITERAL()->getText();

	if (funcCtxt.top().addEntry(literalName, context->type()->getText(), 4)) { // todo : la taille selon le type
		int count = 1;
		std::cout
			<< "  movl $" << cteVal << ", " << (-1 * funcCtxt.top().get(literalName)->bp_offset) << "(%rbp)\n";
	} else {
		// -> erreur ici ? variable serait déjà déclarée dans le scope 
	}

	
	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitDeclareVar(ifccParser::DeclareVarContext *context) 
{
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignVar(ifccParser::AssignVarContext *context)
{
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignConst(ifccParser::AssignConstContext *context)
{
	return 0;
}



antlrcpp::Any visitAssignExpr(ifccParser::AssignExprContext *context) { };

antlrcpp::Any visitOperatorSub(ifccParser::OperatorSubContext *context) { };

antlrcpp::Any visitOperatorPar(ifccParser::OperatorParContext *context) { };

antlrcpp::Any visitOperatorDiv(ifccParser::OperatorDivContext *context) { };

antlrcpp::Any visitOperatorAdd(ifccParser::OperatorAddContext *context) { };

antlrcpp::Any visitLiteralExpr(ifccParser::LiteralExprContext *context) { };

antlrcpp::Any visitOperatorMult(ifccParser::OperatorMultContext *context) { };
