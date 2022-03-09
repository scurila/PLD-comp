#include "CodeGenVisitor.h"
#include "Utils.h"
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

	visit(context->children[1]); // visit expr

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

std::string currentChainedDeclarationType;

antlrcpp::Any CodeGenVisitor::visitDeclareVar(ifccParser::DeclareVarContext *context) 
{
	std::cout << "# declare var\n";
	std::string type = context->type()->children[0]->getText();
	currentChainedDeclarationType = type;

	visit(context->children[1]);

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitLiterallist(ifccParser::LiterallistContext *context) 
{
	std::cout << "# literal list element\n";

	std::string literalName = context->LITERAL()->getText();
	
	funcCtxt.top().addEntry(literalName, currentChainedDeclarationType, typeSize(currentChainedDeclarationType));

	return visitChildren(context);
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
	
	visit(context->children[2]); // explore expr
	
	std::cout << "# assign expr\n";

	std::string literal = context->LITERAL()->getText();
	Entry *literalEntry = funcCtxt.top().get(literal);

	std::cout << "  popq %rax\n" 
			  << "  movl %eax, " << -literalEntry->bp_offset << "(%rbp)\n";

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorSub(ifccParser::OperatorSubContext *context) {

	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack 

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

	std::cout << "  movl " << -literalEntry->bp_offset << "(%rbp), %eax\n"
			  << "  pushq %rax\n" ;

	return 0;
 }

antlrcpp::Any CodeGenVisitor::visitConstExpr(ifccParser::ConstExprContext *ctx) 
{
	std::cout << "# const expr\n";
	int val = stoi(ctx->CONST()->getText());
	std::cout << "  pushq $0x" << std::hex << val << std::dec << std::endl;  // converted to hex to handle negative values (but grammar does not handle it so it is untested for now)
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitOperatorMult(ifccParser::OperatorMultContext *context) { 
	std::cout << "# mult\n";

	visit(context->children[0]);// pushes result in the stack 
	visit(context->children[2]);// pushes result in the stack 

	std::cout<<	"  popq %rbx\n"//right member
			 << "  popq %rax\n"//left member
			 << "  imul %rbx, %rax\n"//signed multiplication between a and b stored in a
			 << "  pushq %rax\n";

	return 0;
}
