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

	if (funcCtxt.top().addEntry(literalName, context->type()->getText())) { 
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
	std::string type = context->type()->getText();
	std::vector<antlr4::tree::TerminalNode *> literals = context->LITERAL();
	for(std::vector<antlr4::tree::TerminalNode *>::iterator it = begin(literals); it != end(literals); ++it) {
    	string literalName = (*it)->getText();
		if (!funcCtxt.top().addEntry(literalName, type)) { 
			// -> erreur ici ? variable serait déjà déclarée dans le scope 
		}
	}	

	cout << funcCtxt.top().get("b") << endl;

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignVar(ifccParser::AssignVarContext *context)
{
	string var1 = context->LITERAL()[0]->getText();
	string var2 = context->LITERAL()[1]->getText();

	std::cout 
		<< "  movl	"<< -1* funcCtxt.top().get(var2)->bp_offset <<"(%rbp), " << "(%eax)\n";
	std::cout
		<< "  movl	 %eax, " <<  -1*funcCtxt.top().get(var1)->bp_offset <<"(%rbp)\n";	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignConst(ifccParser::AssignConstContext *context)
{
	int index = 4; //TODO
	std::cout
		<< "  movl	 $" << context->CONST()->getText()<<", "<< -1*index <<"(%rbp)\n";	
	return 0;
}
