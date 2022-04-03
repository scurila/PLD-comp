#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "generated/ifccLexer.h"
#include "generated/ifccParser.h"
#include "generated/ifccBaseVisitor.h"

#include "CodeGenVisitor.h"
#include "IR/IR.h"
#include "Program.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv)
{
    stringstream in;
    if (argn == 2)
    {
        ifstream lecture(argv[1]);
        in << lecture.rdbuf();
    }
    else
    {
        cerr << "usage: ifcc path/to/file.c" << endl;
        exit(1);
    }

    Arch selectedArch = x86;


    ANTLRInputStream input(in.str());

    ifccLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    ifccParser parser(&tokens);
    tree::ParseTree *tree = parser.axiom();

    if (parser.getNumberOfSyntaxErrors() != 0)
    {
        cerr << "error: syntax error during parsing" << endl;
        exit(1);
    }

    Program *program = new Program();

    CodeGenVisitor v(program);
    v.visit(tree);

	program->gen_asm(std::cout, selectedArch);

    return 0;
}
