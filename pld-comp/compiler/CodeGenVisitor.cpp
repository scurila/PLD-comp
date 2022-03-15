#include "CodeGenVisitor.h"
#include "Exceptions.h"
#include <string>
#include <stack>

#define APPLE 1

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
	std::cout << ".text\n";
	#ifdef APPLE
		std::cout << ".globl _main\n"
			  << "_main: \n";
	#else
		std::cout << ".globl main\n"
					<< "main: \n";
	# endif
		std::cout << "  pushq %rbp\n"
			<< "  movq %rsp, %rbp\n";

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

	try {
		funcCtxt.top().addEntry(literalName, context->type()->getText());
		std::cout
			<< "  movl $" << cteVal << ", " << (-1 * funcCtxt.top().get(literalName)->bp_offset) << "(%rbp)\n";
	} catch (DeclaredVarException e) {
		errorMessage(e.message());
		// todo : return différent ? 
	}
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
		std::cout 
			<< "  movl	"<< -1* funcCtxt.top().get(var2)->bp_offset <<"(%rbp), " << "(%eax)\n";
		std::cout
			<< "  movl	 %eax, " <<  -1*funcCtxt.top().get(var1)->bp_offset <<"(%rbp)\n";	
	} catch (UndeclaredVarException e) {
		errorMessage(e.message());
		// todo : return différent ? 
	}
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitAssignConst(ifccParser::AssignConstContext *context)
{
	int index = 4; //TODO
	std::cout
		<< "  movl	 $" << context->CONST()->getText()<<", "<< -1*index <<"(%rbp)\n";	
	return 0;
}
