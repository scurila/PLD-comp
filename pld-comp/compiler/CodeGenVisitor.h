#pragma once


#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"


class  CodeGenVisitor : public ifccBaseVisitor {
	public:
		virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override ;

		
		virtual antlrcpp::Any visitReturnConst(ifccParser::ReturnConstContext *context) override;

		virtual antlrcpp::Any visitInitVarConst(ifccParser::InitVarConstContext *context) override;

		virtual antlrcpp::Any visitDeclareVar(ifccParser::DeclareVarContext *context) override;

		virtual antlrcpp::Any visitAssignVar(ifccParser::AssignVarContext *context) override;

		virtual antlrcpp::Any visitAssignConst(ifccParser::AssignConstContext *context) override;
};

