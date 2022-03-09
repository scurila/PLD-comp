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

	visit(context->children[2]); // visit expr

	std::cout << "# return\n";
	
	std::cout << "  popq %rax\n"
			  << "  popq %rbp\n"
			  << "  ret\n";

	
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
	
	std::cout << "# init var\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitDeclareVar(ifccParser::DeclareVarContext *context) 
{
	std::cout << "# declare var\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignVar(ifccParser::AssignVarContext *context)
{
	std::cout << "# assign var\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignConst(ifccParser::AssignConstContext *context)
{
	std::cout << "# assign const\n";
	return 0;
}


antlrcpp::Any CodeGenVisitor::visitAssignExpr(ifccParser::AssignExprContext *context) { 
	
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack 
	
	std::cout << "# assign expr\n";

	std::string literal = context->LITERAL()->getText();
	// Entry* literalEntry = funcCtxt.top().get(literal);

	std::cout << "  popq %rax\n" 
			  << "  movq %rax, " << /*-literalEntry->bp_offset << */"(%rbp)\n";

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorSub(ifccParser::OperatorSubContext *context) {
	std::cout << "# sub\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorPar(ifccParser::OperatorParContext *context) {
	std::cout << "# par\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorDiv(ifccParser::OperatorDivContext *context) { 
	std::cout << "# divide\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorAdd(ifccParser::OperatorAddContext *context) {
	
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack 

	std::cout << "# add\n";

	std::cout<<	"  popq %rbx\n"//right member
			 << "  popq %rax\n"//left member
			 << "  add %rax, %rbx\n"
			 << "  pushq %rbx\n";
	
	return 0; 
 }

antlrcpp::Any CodeGenVisitor::visitLiteralExpr(ifccParser::LiteralExprContext *context) {
	std::cout << "# literal expr\n";
	return 0;
 }

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) 
{
	std::cout << "# const expr\n";
	int val = stoi(ctx->CONST()->getText());
	std::cout << "  pushq $" << val << std::endl;
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorMult(ifccParser::OperatorMultContext *context) { 
	std::cout << "# mult\n";
	return 0;
}
