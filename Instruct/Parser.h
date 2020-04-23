#pragma once
#include "Token.h"
#include "Node.h"
#include "Scanner.h"

// We are currently
// supporting only three kinds of statements – DeclarationStatements,
// AssignmentStatements, and CoutStatements.
// They begin with INT_TOKEN,
// IDENTIFIER_TOKEN, and COUT_TOKEN tokens respectively.

class ParserClass {
public:
	ParserClass(SymbolTableClass* sT, ScannerClass* s);
	StartNode* Start();
	ProgramNode* Program();
	BlockNode* Block();
	StatementGroupNode* StatementGroup();
	StatementNode* Statement();
	TokenClass Match(TokenType expectedType);
	ExpressionNode* Expression();
	ExpressionNode* Relational();
	ExpressionNode* PlusMinus();
	ExpressionNode* TimesDivide();
	ExpressionNode* And();
	ExpressionNode* Or();
	ExpressionNode* Factor();
	IdentifierNode* Identifier();
	IntegerNode* Integer();
	DeclarationStatementNode* DeclarationStatement();
	StatementNode* AssignmentStatement();
	CoutStatementNode* CoutStatement();
	IfStatementNode* IfStatement();
	WhileStatementNode* WhileStatement();
	
private:
	ScannerClass* mScanner;
	SymbolTableClass* mSymbolTable;
};
