#pragma once


#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"


class  CodeGenVisitor : public ifccBaseVisitor {
	public:
		virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override ;

		
		virtual antlrcpp::Any visitReturnConst(ifccParser::ReturnConstContext *context) override;

		virtual antlrcpp::Any visitInitVarCte(ifccParser::InitVarCteContext *context) override;

};

