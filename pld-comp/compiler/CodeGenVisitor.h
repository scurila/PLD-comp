#pragma once


#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "SymbolTable.h"
#include "IR/IR.h"
#include "Program.h"

#include <stack>


class  CodeGenVisitor : public ifccBaseVisitor {
	public:

        CodeGenVisitor(Program *program): program(program) {};

		virtual antlrcpp::Any visitMain(ifccParser::MainContext *ctx) override ;

		virtual antlrcpp::Any visitDeclareFunc(ifccParser::DeclareFuncContext *ctx) override;

		virtual antlrcpp::Any visitInstrblock(ifccParser::InstrblockContext *ctx) override;
		
		virtual antlrcpp::Any visitReturnExpr(ifccParser::ReturnExprContext *context) override;

		virtual antlrcpp::Any visitReturnVoid(ifccParser::ReturnVoidContext *ctx) override;

		virtual antlrcpp::Any visitInitVarConst(ifccParser::InitVarConstContext *context) override;
		
		virtual antlrcpp::Any visitInitVarExpr(ifccParser::InitVarExprContext *ctx) override;

		virtual antlrcpp::Any visitDeclareVar(ifccParser::DeclareVarContext *context) override;  
		
		// virtual antlrcpp::Any visitLiterallist(ifccParser::LiterallistContext *context) override;

		virtual antlrcpp::Any visitAssignVar(ifccParser::AssignVarContext *context) override;

		virtual antlrcpp::Any visitAssignConst(ifccParser::AssignConstContext *context) override;

		virtual antlrcpp::Any visitAssignExpr(ifccParser::AssignExprContext *context) override;

    	virtual antlrcpp::Any visitOperatorPar(ifccParser::OperatorParContext *context) override;


    	// virtual antlrcpp::Any visitOperatorDiv(ifccParser::OperatorDivContext *context) override;

    	virtual antlrcpp::Any visitOperatorMultDivMod(ifccParser::OperatorMultDivModContext *context) override;

    	virtual antlrcpp::Any visitOperatorAddSub(ifccParser::OperatorAddSubContext *context) override;

    	// virtual antlrcpp::Any visitOperatorSub(ifccParser::OperatorSubContext *context) override;

		virtual antlrcpp::Any visitOperatorBinary(ifccParser::OperatorBinaryContext *context) override;

    	virtual antlrcpp::Any visitLiteralExpr(ifccParser::LiteralExprContext *context) override;

  		virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override;

		virtual antlrcpp::Any visitOperatorCmp(ifccParser::OperatorCmpContext *ctx) override;

		virtual antlrcpp::Any visitOperatorUnaryPrefix(ifccParser::OperatorUnaryPrefixContext *ctx) override;

		virtual antlrcpp::Any visitCharExpr(ifccParser::CharExprContext *context) override;

		virtual antlrcpp::Any visitCallFuncNoArgs(ifccParser::CallFuncNoArgsContext *ctx) override;

  		virtual antlrcpp::Any visitCallFuncArgs(ifccParser::CallFuncArgsContext *ctx) override;

		virtual antlrcpp::Any visitIfElseIfElse(ifccParser::IfElseIfElseContext *ctx) override;

		virtual antlrcpp::Any visitWhileLoop(ifccParser::WhileLoopContext *ctx) override;
	
		virtual antlrcpp::Any visitExprAlone(ifccParser::ExprAloneContext *ctx) override; 
  
	private:
		// Alias methods for lighter code
		CFG* cur_cfg() const { return program->current_cfg; }
		void set_cfg(CFG *cfg) { program->current_cfg = cfg; }

		Program *program;
};

