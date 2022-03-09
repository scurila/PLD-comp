#pragma once


#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "SymbolTable.h"
#include <stack>


class  CodeGenVisitor : public ifccBaseVisitor {
	public:
		virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override ;
		
		virtual antlrcpp::Any visitReturnExpr(ifccParser::ReturnExprContext *context) override;

		virtual antlrcpp::Any visitInitVarConst(ifccParser::InitVarConstContext *context) override;

		virtual antlrcpp::Any visitDeclareVar(ifccParser::DeclareVarContext *context) override;

		virtual antlrcpp::Any visitAssignVar(ifccParser::AssignVarContext *context) override;

		virtual antlrcpp::Any visitAssignConst(ifccParser::AssignConstContext *context) override;

		virtual antlrcpp::Any visitAssignExpr(ifccParser::AssignExprContext *context) override;

    	virtual antlrcpp::Any visitOperatorSub(ifccParser::OperatorSubContext *context) override;

    	virtual antlrcpp::Any visitOperatorPar(ifccParser::OperatorParContext *context) override;

    	virtual antlrcpp::Any visitOperatorDiv(ifccParser::OperatorDivContext *context) override;

    	virtual antlrcpp::Any visitOperatorAdd(ifccParser::OperatorAddContext *context) override;

    	virtual antlrcpp::Any visitLiteralExpr(ifccParser::LiteralExprContext *context) override;

  		virtual antlrcpp::Any visitConstExpr(ifccParser::ConstExprContext *ctx) override;

    	virtual antlrcpp::Any visitOperatorMult(ifccParser::OperatorMultContext *context) override;


		
		// TEMPORAIRE
		stack<SymbolTable> funcCtxt;
};

