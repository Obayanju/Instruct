#pragma once
#include <vector>
#include <string>
#include "Symbol.h"
#include "Debug.h"
#include "instructions.h"
/*
 Terminals: ENDFILE, VOID, MAIN, LPAREN, RPAREN, LCURLY, RCURLY,
INT, SEMICOLON, ASSIGNMENT, COUT, INSERTION, PLUS,
IDENTIFIER, INTEGER

Nonterminals: <Start>, <Program>, <Block>, <StatementGroup>, <Statement>
<DeclarationStatement>, <AssignmentStatement>,
<CoutStatement>, <Expression>, <Identifier>, <Integer>
*/
using namespace std;
class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class IdentifierNode;
class IntegerNode;
class ExpressionNode;
class CoutStatementNode;
class BinaryOperatorNode;
class PlusNode;
class PlusEqualNode;
class MinusNode;
class MinusEqualNode;
class TimesNode;
class DivideNode;
class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class AndNode;
class OrNode;


class Node {
public:
	Node();
	virtual ~Node();
	virtual void Interpret()=0;
	virtual void Code(InstructionsClass& machineCode) = 0;
};

class StartNode : public Node {
public:
	StartNode(ProgramNode *pn);
	~StartNode();
	ProgramNode* mProgramNode;
	void Interpret();
	void Code(InstructionsClass& machineCode);
private:
};

class ProgramNode : public Node {
public:
	ProgramNode(BlockNode * bn);
	~ProgramNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
private:
	BlockNode* mBlockNode;
};

class StatementNode : public Node {
public:
	StatementNode();
	~StatementNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
private:
};

class BlockNode : public StatementNode {
public:
	BlockNode(StatementGroupNode * sgn);
	~BlockNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
	StatementGroupNode* mStatementGNode;
};

class StatementGroupNode : public Node {
public:
	StatementGroupNode();
	~StatementGroupNode();
	void AddStatement(StatementNode* sNode);
	void Interpret();
	void Code(InstructionsClass& machineCode);
private:
	vector<StatementNode*> sNodes;
};


class DeclarationStatementNode : public StatementNode {
public:
	DeclarationStatementNode(IdentifierNode* iN);
	~DeclarationStatementNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
	IdentifierNode* mIdentifierNode;
private:
};

class AssignmentStatementNode : public StatementNode {
public:
	AssignmentStatementNode(IdentifierNode * iNode, ExpressionNode * exNode);
	~AssignmentStatementNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
private:
	IdentifierNode * mIdentNode;
	ExpressionNode * mExNode;
};

class CoutStatementNode : public StatementNode {
public:
	CoutStatementNode();
	~CoutStatementNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
	void AddExpression(ExpressionNode* en);
	vector<ExpressionNode*> mExNode;
};

class IfStatementNode : public StatementNode {
public:
	IfStatementNode(ExpressionNode* en, StatementNode* sn);
	~IfStatementNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
	ExpressionNode* mExpression;
	StatementNode* mStatement;
};

class WhileStatementNode : public StatementNode {
public:
	WhileStatementNode(ExpressionNode* en, StatementNode* sn);
	~WhileStatementNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
	ExpressionNode* mExpression;
	StatementNode* mStatement;
};

class ExpressionNode {
public:
	ExpressionNode();
	virtual int Evaluate();
	virtual ~ExpressionNode();
	virtual void CodeEvaluate(InstructionsClass& machineCode) = 0;
};

// No destructor because IntegerNodes have no nonterminal children
class IntegerNode : public ExpressionNode {
public:
	IntegerNode(int i);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
private:
	int mInt;
};

class IdentifierNode : public ExpressionNode {
public:
	IdentifierNode(string s, SymbolTableClass* sTable);
	void DeclareVariable(); // will be called by DeclarationNodes interpreting themselves
	void SetValue(int v); // will be called by AssignmentNodes interpreting themselves
	int GetIndex(); // needed when writing machine code
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
	SymbolTableClass* mSymbolTable;
private:
	string mLabel;
};

class BinaryOperatorNode : public ExpressionNode {
public:
	BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right);
	virtual ~BinaryOperatorNode();

protected: // so derived classes can directly access it
	ExpressionNode *mLeft;
	ExpressionNode *mRight;
};

class PlusNode : public BinaryOperatorNode {
public:
	PlusNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class PlusEqualNode :public StatementNode {
public:
	PlusEqualNode(IdentifierNode* in, ExpressionNode* en);
	~PlusEqualNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
	IdentifierNode* mIn;
	ExpressionNode* mEn;
};

class MinusNode : public BinaryOperatorNode {
public:
	MinusNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class MinusEqualNode :public StatementNode {
public:
	MinusEqualNode(IdentifierNode* in, ExpressionNode* en);
	~MinusEqualNode();
	void Interpret();
	void Code(InstructionsClass& machineCode);
	IdentifierNode* mIn;
	ExpressionNode* mEn;
};

class TimesNode : public BinaryOperatorNode {
public:
	TimesNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class DivideNode : public BinaryOperatorNode {
public:
	DivideNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class LessNode : public BinaryOperatorNode {
public:
	LessNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class LessEqualNode : public BinaryOperatorNode {
public:
	LessEqualNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class GreaterNode : public BinaryOperatorNode {
public:
	GreaterNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
	GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class EqualNode : public BinaryOperatorNode {
public:
	EqualNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class NotEqualNode : public BinaryOperatorNode {
public:
	NotEqualNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class AndNode : public BinaryOperatorNode {
public:
	AndNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};

class OrNode : public BinaryOperatorNode {
public:
	OrNode(ExpressionNode* left, ExpressionNode* right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass& machineCode);
};
