#include "CodeGenVisitor.h"
#include <string>

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
	std::cout << ".text\n"
	          << ".globl main\n"
			  << "main: \n" 
			  << "  pushq %rbp\n"
			  << "  movq %rsp, %rbp\n";

	return visitChildren(ctx);
}

		
antlrcpp::Any CodeGenVisitor::visitReturnConst(ifccParser::ReturnConstContext *context) 
{ 
	int retval = stoi(context->CONST()->getText());
	std::cout 
			<< "  movl $" << retval << ", %eax\n"
			<< "  popq %rbp\n"
	 		<< "  ret\n";

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitInitVarCte(ifccParser::InitVarCteContext *context)
{
	int cteVal = stoi(context->CONST()->getText());
	std::string literalName = context->LITERAL()->getText();

	int count = 1;

	std::cout
		<< "  movl $" << cteVal << ", " << (-4 * count) << "(%rbp)";
	return 0;
}
