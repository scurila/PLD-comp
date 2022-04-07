#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <exception>
#include <string>

#include "antlr4-runtime.h"
#include "generated/ifccLexer.h"
#include "generated/ifccParser.h"
#include "generated/ifccBaseVisitor.h"

#include "CodeGenVisitor.h"
#include "IR/IR.h"
#include "Program.h"
#include "Exceptions.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv)
{
    stringstream in;
    if (argn >= 2)
    {
        ifstream lecture(argv[1]);
        in << lecture.rdbuf();
    }
    else
    {
        cerr << "usage: ifcc path/to/file.c [args]" << endl;
        exit(1);
    }

    Arch selectedArch = arm;

    for(int i = 2; i < argn; i++) {
        string arg = argv[i];
        if(arg.rfind("--arch=") == 0) {
            string val = arg.substr(7);
            if(val == "arm") selectedArch = arm;
            else if(val == "x86") selectedArch = x86;
        }
    }

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

    try {
        CodeGenVisitor v(program);
        v.visit(tree);
    }
    catch(const ifccException *e) {
        std::cerr << "An error occurred during tree exploration: \n";
        std::cerr << e->message() << std::endl;
    }
    /*catch(UndeclaredVarException &e) {
        std::cerr << e.message() << std::endl;
    }*/
    
    try {    
	    program->gen_asm(std::cout, selectedArch);
    }
    catch(const ifccException *e) {
        std::cerr << "An error occurred during code generation: \n";
        std::cerr << e->message() << std::endl;
    }

    return 0;
}
