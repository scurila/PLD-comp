#include "CodeGenVisitor.h"
#include "Utils.h"
#include "Exceptions.h"
#include "IR/instr.h"
#include <string>
#include <stack>

#define APPLE 0

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

	// TODO: temporary as we need to know the number of variables allocated (this needs IR set up, or a pre-run on the code to identify variables)
	std::cout 
			<< "  movq %rsp, %rax\n"
			<< "  subq $0x100, %rax\n"
			<< "  movq %rax, %rsp\n";
	
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
	/*int retval = stoi(context->CONST()->getText());
	std::cout 
			<< "  movl $" << retval << ", %eax\n"
			<< "  popq %rbp\n"
	 		<< "  ret\n";
*/

	visit(context->children[1]); // visit expr

	std::cout << "# return expr\n";
	
	std::cout << "  popq %rax\n"; // store returned value in rax

	std::cout   // move rsp to pop rbp later
			<< "  movq %rsp, %rbx\n"
			<< "  addq $0x100, %rbx\n"
			<< "  movq %rbx, %rsp\n";

	std::cout  // restore rsp (and remove rbp from stack)
			  << "  popq %rbp\n"
			  << "  ret\n";

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
	std::cout << "# assign var\n";
	
	string var1 = context->LITERAL()[0]->getText();
	string var2 = context->LITERAL()[1]->getText();

	try {
	    cfg->current_bb->add_IRInstr(new IRInstr_copy(cfg->current_bb, var1, var2));
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
	std::cout << "# assign const\n";
	
	try {
		std::string literal = context->LITERAL()->getText();
		int index = funcCtxt.top().get(literal)->bp_offset;
		std::cout
			<< "  movl $0x" << std::hex << stoi(context->CONST()->getText()) << std::dec << ", "<< -1*index <<"(%rbp)\n";
		cfg->current_bb->add_IRInstr(new IRInstr_ldconst(cfg->current_bb, literal, stoi(context->CONST()->getText())));

	} catch (UndeclaredVarException e) {
		errorMessage(e.message());
	}
	return 0;
}


antlrcpp::Any CodeGenVisitor::visitAssignExpr(ifccParser::AssignExprContext *context) { 
	
	visit(context->children[2]); // explore expr
	
	std::cout << "# assign expr\n";

	std::string literal = context->LITERAL()->getText();
	Entry *literalEntry = funcCtxt.top().get(literal);

    cfg->current_bb->add_IRInstr(new IRInstr_popvar(cfg->current_bb, literal));

	std::cout << "  popq %rax\n" 
			  << "  movl %eax, " << -literalEntry->bp_offset << "(%rbp)\n";

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorSub(ifccParser::OperatorSubContext *context) {

	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack

	cfg->current_bb->add_IRInstr(new IRInstr_sub(cfg->current_bb));

	std::cout << "# sub\n";

	std::cout<<	"  popq %rbx\n"//right member
			 << "  popq %rax\n"//left member
			 << "  sub %rbx, %rax\n"//substract b from a and stores result in a 
			 << "  pushq %rax\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorPar(ifccParser::OperatorParContext *context) {
	std::cout << "# par\n";
	return visitChildren(context);
}

antlrcpp::Any CodeGenVisitor::visitOperatorDiv(ifccParser::OperatorDivContext *context) { 

	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack

	cfg->current_bb->add_IRInstr(new IRInstr_div(cfg->current_bb));

	std::cout << "# divide\n";

	std::cout<<	"  popq %rbx\n"//right member
			 << "  popq %rax\n"//left member
			 << "  idiv %rbx\n"//The idiv instruction divides the contents of the 64-bit integer EDX:EAX by the specified operand value.
			 << "  pushq %rax\n";//The quotient result of the division is stored into EAX

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorAdd(ifccParser::OperatorAddContext *context) {
	
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack 
    cfg->current_bb->add_IRInstr(new IRInstr_add(cfg->current_bb));
	std::cout << "# add\n";

	std::cout<<	"  popq %rbx\n"//right member
			 << "  popq %rax\n"//left member
			 << "  add %rbx, %rax\n"// add a and b and stores result in a
			 << "  pushq %rax\n";
	
	return 0; 
 }

antlrcpp::Any CodeGenVisitor::visitLiteralExpr(ifccParser::LiteralExprContext *context) {
	std::cout << "# read literal expr\n";

	std::string literal = context->LITERAL()->getText();
	Entry *literalEntry = funcCtxt.top().get(literal);

    cfg->current_bb->add_IRInstr(new IRInstr_pushvar(cfg->current_bb,literal));
	std::cout << "  movl " << -literalEntry->bp_offset << "(%rbp), %eax\n"
			  << "  pushq %rax\n" ;

	return 0;
 }

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) 
{
	std::cout << "# const expr\n";
	int val = stoi(ctx->CONST()->getText());
	cfg->current_bb->add_IRInstr(new IRInstr_pushconst(cfg->current_bb, val));
	std::cout << "  pushq $0x" << std::hex << val << std::dec << std::endl;  // converted to hex to handle negative values (but grammar does not handle it so it is untested for now)
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorMult(ifccParser::OperatorMultContext *context) { 
	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack 

    cfg->current_bb->add_IRInstr(new IRInstr_mul(cfg->current_bb));

	std::cout << "# mult\n";

	std::cout<<	"  popq %rbx\n"//right member
			 << "  popq %rax\n"//left member
			 << "  imul %rbx, %rax\n"//signed multiplication between a and b stored in a
			 << "  pushq %rax\n";

	return 0;
}
