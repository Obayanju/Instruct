#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

StartNode::StartNode(ProgramNode* pn)
{
	//MSG("init start node");
	mProgramNode = pn;
}

StartNode::~StartNode()
{
	//MSG("delete start node");
	delete(mProgramNode);
}

void StartNode::Interpret()
{
	mProgramNode->Interpret();
}

void StartNode::Code(InstructionsClass& machineCode)
{
	mProgramNode->Code(machineCode);

}

ProgramNode::ProgramNode(BlockNode * bn)
{
	//MSG("init program node");
	mBlockNode = bn;
}

void ProgramNode::Interpret()
{
	mBlockNode->Interpret();
}

void ProgramNode::Code(InstructionsClass& machineCode)
{
	mBlockNode->Code(machineCode);
}

ProgramNode::~ProgramNode()
{
	//MSG("delete program node");
	delete(mBlockNode);
}

BlockNode::BlockNode(StatementGroupNode * sgn)
{
	//MSG("init BlockNode");
	mStatementGNode = sgn;
}

void BlockNode::Interpret()
{
	mStatementGNode->Interpret();
}

void BlockNode::Code(InstructionsClass& machineCode)
{
	mStatementGNode->Code(machineCode);
}

BlockNode::~BlockNode()
{
	delete(mStatementGNode);
	//MSG("delete block node");
}

StatementGroupNode::StatementGroupNode()
{
	//MSG("init statement group node");
}

void StatementGroupNode::Interpret()
{
	for (int i = 0; i < sNodes.size(); i++)
	{
		sNodes[i]->Interpret();
	}
}

void StatementGroupNode::Code(InstructionsClass& machineCode)
{
	for (int i = 0; i < sNodes.size(); i++)
	{
		sNodes[i]->Code(machineCode);
	}
}

StatementGroupNode::~StatementGroupNode()
{
	for (int i = 0; i < sNodes.size(); i++) {
		delete sNodes[i];
	}
	//MSG("delete statement group nodes");
}

void StatementGroupNode::AddStatement(StatementNode* sNode)
{
	sNodes.push_back(sNode);
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* iNode, ExpressionNode* exNode)
{
	mIdentNode = iNode;
	mExNode = exNode;
	//MSG("init assignment statement node");
}

void AssignmentStatementNode::Interpret()
{
	mIdentNode->SetValue(mExNode->Evaluate());
}

void AssignmentStatementNode::Code(InstructionsClass& machineCode)
{
	mExNode->CodeEvaluate(machineCode);
	int index = mIdentNode->GetIndex();
	machineCode.PopAndStore(index);
}

AssignmentStatementNode::~AssignmentStatementNode()
{
	//MSG("delete assignment - identifier node");
	delete(mIdentNode);
	//MSG("delete assignment - expression node");
	delete(mExNode);
}

ExpressionNode::ExpressionNode()
{
}

int ExpressionNode::Evaluate()
{
	return 0;
}

ExpressionNode::~ExpressionNode()
{
	//MSG("delete Expression Node");
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* iN)
{
	//MSG("init declaration statement node");
	mIdentifierNode = iN;
}

void DeclarationStatementNode::Interpret()
{
	mIdentifierNode->DeclareVariable();
}

void DeclarationStatementNode::Code(InstructionsClass& machineCode)
{
	mIdentifierNode->DeclareVariable();
}

DeclarationStatementNode::~DeclarationStatementNode()
{
	delete(mIdentifierNode);
	//MSG("delete declaration statement node");
}

CoutStatementNode::CoutStatementNode()
{
}

void CoutStatementNode::Interpret()
{
	for (int i = 0; i < mExNode.size(); i++) {
		int eval = mExNode[i]->Evaluate();
		cout << eval;
	}
}

void CoutStatementNode::Code(InstructionsClass& machineCode)
{
	for (int i = 0; i < mExNode.size(); i++) {
		mExNode[i]->CodeEvaluate(machineCode);
		machineCode.PopAndWrite();
	}
}

void CoutStatementNode::AddExpression(ExpressionNode* en)
{
	mExNode.push_back(en);
}

CoutStatementNode::~CoutStatementNode()
{
	for (int i = 0; i < mExNode.size(); i++) {
		delete mExNode[i];
	}
	MSG("CoutNode Deleting");
}

IntegerNode::IntegerNode(int i)
{
	mInt = i;
}

int IntegerNode::Evaluate()
{
	return mInt;
}

void IntegerNode::CodeEvaluate(InstructionsClass& machineCode)
{
	machineCode.PushValue(mInt);
}

IdentifierNode::IdentifierNode(string s, SymbolTableClass* sTable)
{
	cout << "init symbol table" << endl;
	mLabel = s;
	mSymbolTable = sTable;
}

void IdentifierNode::DeclareVariable()
{
	mSymbolTable->AddEntry(mLabel);
}

void IdentifierNode::SetValue(int v)
{
	mSymbolTable->SetValue(mLabel, v);
}

int IdentifierNode::GetIndex()
{
	int index = mSymbolTable->GetIndex(mLabel);
	return index;
}

int IdentifierNode::Evaluate() 
{
	return mSymbolTable->GetValue(mLabel);
}

void IdentifierNode::CodeEvaluate(InstructionsClass& machineCode)
{
	machineCode.PushVariable(GetIndex());
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right)
	: ExpressionNode(), mLeft(left), mRight(right)
{
	//MSG("init Binary operator node");
}

BinaryOperatorNode::~BinaryOperatorNode()
{
	delete(mLeft);
	//MSG("delete left BinaryOperator Node");
	delete(mRight);
	//MSG("delete right BinaryOperator Node");
}

PlusNode::PlusNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int PlusNode::Evaluate()
{
	int sum = 0;
	sum += mLeft->Evaluate();
	sum += mRight->Evaluate();
	return sum;
}

void PlusNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLeft->CodeEvaluate(machineCode);
	mRight->CodeEvaluate(machineCode);
	machineCode.PopPopAddPush();
}

StatementNode::StatementNode()
{
	//MSG("init statement node");
}

void StatementNode::Interpret()
{
}

void StatementNode::Code(InstructionsClass& machineCode)
{

}

StatementNode::~StatementNode()
{
}

MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{

}

int MinusNode::Evaluate()
{
	return mLeft->Evaluate() - mRight->Evaluate();
}

void MinusNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLeft->CodeEvaluate(machineCode);
	mRight->CodeEvaluate(machineCode);
	machineCode.PopPopSubPush();
}

TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int TimesNode::Evaluate()
{
	return mLeft->Evaluate() * mRight->Evaluate();
}

void TimesNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLeft->CodeEvaluate(machineCode);
	mRight->CodeEvaluate(machineCode);
	machineCode.PopPopMulPush();
}

DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int DivideNode::Evaluate()
{
	return mLeft->Evaluate() / mRight->Evaluate();
}

void DivideNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLeft->CodeEvaluate(machineCode);
	mRight->CodeEvaluate(machineCode);
	machineCode.PopPopDivPush();
}

LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int LessNode::Evaluate()
{
	return mLeft->Evaluate() < mRight->Evaluate() ? 1 : 0;
}

void LessNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLeft->CodeEvaluate(machineCode);
	mRight->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
}

LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int LessEqualNode::Evaluate()
{
	return mLeft->Evaluate() <= mRight->Evaluate() ? 1 : 0;
}

void LessEqualNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLeft->CodeEvaluate(machineCode);
	mRight->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
}

GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int GreaterNode::Evaluate()
{
	return mLeft->Evaluate() > mRight->Evaluate() ? 1 : 0;
}

void GreaterNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLeft->CodeEvaluate(machineCode);
	mRight->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int GreaterEqualNode::Evaluate()
{
	return mLeft->Evaluate() >= mRight->Evaluate() ? 1 : 0;
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLeft->CodeEvaluate(machineCode);
	mRight->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
}

EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int EqualNode::Evaluate()
{
	return mLeft->Evaluate() == mRight->Evaluate() ? 1 : 0;
}

void EqualNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLeft->CodeEvaluate(machineCode);
	mRight->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
}

NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int NotEqualNode::Evaluate()
{
	return mLeft->Evaluate() != mRight->Evaluate() ? 1 : 0;
}

void NotEqualNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLeft->CodeEvaluate(machineCode);
	mRight->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
}

IfStatementNode::IfStatementNode(ExpressionNode* en, StatementNode* sn)
{
	mExpression = en;
	mStatement = sn;
}

IfStatementNode::~IfStatementNode()
{
	delete mExpression;
	delete mStatement;
}

void IfStatementNode::Interpret()
{
	if (mExpression->Evaluate()) {
		mStatement->Interpret();
	}
}

void IfStatementNode::Code(InstructionsClass& machineCode)
{
	mExpression->CodeEvaluate(machineCode);
	unsigned char* InsertAddress = machineCode.SkipIfZeroStack();
	unsigned char* address1 = machineCode.GetAddress();
	mStatement->Code(machineCode);
	unsigned char* address2 = machineCode.GetAddress();
	machineCode.SetOffset(InsertAddress, (int)(address2 - address1));
}

WhileStatementNode::WhileStatementNode(ExpressionNode* en, StatementNode* sn)
{
	mExpression = en;
	mStatement = sn;
}

WhileStatementNode::~WhileStatementNode()
{
	delete mExpression;
	delete mStatement;
}

void WhileStatementNode::Interpret()
{
	while (mExpression->Evaluate()) {
		mStatement->Interpret();
	}
}

void WhileStatementNode::Code(InstructionsClass& machineCode)
{
	unsigned char* address1 = machineCode.GetAddress();
	mExpression->CodeEvaluate(machineCode);
	unsigned char* InsertAddressToSkip = machineCode.SkipIfZeroStack();
	unsigned char* address2 = machineCode.GetAddress();
	mStatement->Code(machineCode);
	unsigned char* InsertAddressToJump = machineCode.Jump();
	unsigned char* address3 = machineCode.GetAddress();
	machineCode.SetOffset(InsertAddressToSkip, (int)(address3 - address2));
	machineCode.SetOffset(InsertAddressToJump, (int)(address1 - address3));
}

AndNode::AndNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int AndNode::Evaluate()
{
	if (mLeft->Evaluate() && mRight->Evaluate())
		return 1;
	return 0;
}

void AndNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLeft->CodeEvaluate(machineCode);
	mRight->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
}

OrNode::OrNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int OrNode::Evaluate()
{
	if (mLeft->Evaluate() || mRight->Evaluate())
		return 1;
	return 0;
}

void OrNode::CodeEvaluate(InstructionsClass& machineCode)
{
	mLeft->CodeEvaluate(machineCode);
	mRight->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();
}

PlusEqualNode::PlusEqualNode(IdentifierNode* in, ExpressionNode* en)
{
	mIn = in;
	mEn = en;
}

PlusEqualNode::~PlusEqualNode()
{
	delete mIn;
	delete mEn;
	MSG("PlusEqualNode Deleting");
}

void PlusEqualNode::Interpret()
{
	int eval = mEn->Evaluate() + mIn->Evaluate();
	mIn->SetValue(eval);
}

void PlusEqualNode::Code(InstructionsClass& machineCode)
{
	int index = mIn->GetIndex();
	mIn->CodeEvaluate(machineCode);
	mEn->CodeEvaluate(machineCode);
	machineCode.PopPopAddPush();
	machineCode.PopAndStore(index);
}

MinusEqualNode::MinusEqualNode(IdentifierNode* in, ExpressionNode* en)
{
	mIn = in;
	mEn = en;
}

MinusEqualNode::~MinusEqualNode()
{
	delete mIn;
	delete mEn;
	MSG("MinusEqualNode Deleting");
}

void MinusEqualNode::Interpret()
{
	int eval = mIn->Evaluate() - mEn->Evaluate();
	mIn->SetValue(eval);
}

void MinusEqualNode::Code(InstructionsClass& machineCode)
{
	int index = mIn->GetIndex();
	mIn->CodeEvaluate(machineCode);
	mEn->CodeEvaluate(machineCode);
	machineCode.PopPopSubPush();
	machineCode.PopAndStore(index);
}
