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
	/*int retval = stoi(context->CONST()->getText());
	std::cout 
			<< "  movl $" << retval << ", %eax\n"
			<< "  popq %rbp\n"
	 		<< "  ret\n";
*/
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitInitVarConst(ifccParser::InitVarConstContext *context)
{
	/*int cteVal = stoi(context->CONST()->getText());
	std::string literalName = context->LITERAL()->getText();

	if (funcCtxt.top().addEntry(literalName, context->type()->getText(), 4)) { // todo : la taille selon le type
		int count = 1;
		std::cout
			<< "  movl $" << cteVal << ", " << (-1 * funcCtxt.top().get(literalName)->bp_offset) << "(%rbp)\n";
	} else {
		// -> erreur ici ? variable serait déjà déclarée dans le scope 
	}
*/
	
	
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


antlrcpp::Any CodeGenVisitor::visitAssignExpr(ifccParser::AssignExprContext *context) { 
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorSub(ifccParser::OperatorSubContext *context) {
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorPar(ifccParser::OperatorParContext *context) {
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorDiv(ifccParser::OperatorDivContext *context) { 
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorAdd(ifccParser::OperatorAddContext *context) {
	
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[1]);// pushes result in the stack 

	std::cout<<	"popq %ebx\n"//right member
			<<"popq %eax\n"//left member
			<< "add %eax, %ebx"
			<< "pushq %ebx";
	
	return 0; 
 }

antlrcpp::Any CodeGenVisitor::visitLiteralExpr(ifccParser::LiteralExprContext *context) {
	return 0;
 }

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) 
{
	/*int val = stoi(ctx->CONST()->getText());
	std::cout << "pushq $" << val << std::endl;*/
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorMult(ifccParser::OperatorMultContext *context) { 
	return 0;
}
