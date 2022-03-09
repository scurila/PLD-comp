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

antlrcpp::Any CodeGenVisitor::visitInitVarConst(ifccParser::InitVarConstContext *context)
{
	int cteVal = stoi(context->CONST()->getText());
	std::string literalName = context->LITERAL()->getText();

	int count = 1;

	std::cout
		<< "  movl $" << cteVal << ", " << (-4 * count) << "(%rbp)\n";
	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitDeclareVar(ifccParser::DeclareVarContext *context) 
{
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignVar(ifccParser::AssignVarContext *context)
{
	string var1 = context->LITERAL(0)->getText();
	string var2 = context->LITERAL(1)->getText();
	  
	int index = 4; //TODO
	std::cout 
		<< "  movl	"<< -1*index <<"(%rbp), " << "(%eax)\n";
	std::cout
		<< "  movl	 %eax, " <<  -1*index <<"(%rbp)\n";	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignConst(ifccParser::AssignConstContext *context)
{
	int index = 4; //TODO
	std::cout
		<< "  movl	 $" << context->CONST()->getText()<<", "<< -1*index <<"(%rbp)\n";	
	return 0;
}
