#include "CodeGenVisitor.h"

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
	std::cout << ".text\n.globl main\nmain: \n";

	/*int retval = stoi(ctx->CONST()->getText());
	std::cout<<".globl	main\n"
		" main: \n"
		" 	movl	$"<<retval<<", %eax\n"
		" 	ret\n";
*/
	return 0;
}

		
antlrcpp::Any CodeGenVisitor::visitReturnConst(ifccParser::ReturnConstContext *context) 
{ 
	std::cout << "hello";
	int retval = stoi(context->CONST()->getText());
	std::cout << "  movl $" << retval << ", %eax\n"
	 		<< "ret\n";

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitDeclareVar(ifccParser::DeclareVarContext *context)
{
	return 0;
}
