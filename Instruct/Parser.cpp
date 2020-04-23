#include "Parser.h"

ParserClass::ParserClass(SymbolTableClass* sT, ScannerClass* s)
	//: mScanner(s), mSymbolTable(sT)
{
	mSymbolTable = sT;
	mScanner = s;
}

StartNode * ParserClass::Start()
{
	ProgramNode* pn = Program();
	Match(EOF_TOKEN);
	StartNode* sn = new StartNode(pn);
	return sn;
}

ProgramNode* ParserClass::Program()
{
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	BlockNode* bN = Block();
	ProgramNode* pNode = new ProgramNode(bN);
	return pNode;
}

BlockNode* ParserClass::Block()
{
	Match(LCURLY_TOKEN);
	StatementGroupNode* sgn = StatementGroup();
	Match(RCURLY_TOKEN);
	BlockNode* bn = new BlockNode(sgn);
	return bn;
}

StatementGroupNode* ParserClass::StatementGroup()
{
	StatementGroupNode* sgn = new StatementGroupNode();
	while (true) {
		StatementNode* sN = Statement();
		if (sN == NULL) break;
		sgn->AddStatement(sN);
	}
	return sgn;
}

StatementNode* ParserClass::Statement()
{
	TokenClass t = mScanner->PeekNextToken();
	if (t.GetTokenType() == INT_TOKEN) {
		return DeclarationStatement();
	}
	else if (t.GetTokenType() == IDENTIFIER_TOKEN) {
		return AssignmentStatement();
	}
	else if (t.GetTokenType() == COUT_TOKEN) {
		return CoutStatement();
	}
	else if (t.GetTokenType() == LCURLY_TOKEN) {
		return Block();
	}
	else if (t.GetTokenType() == IF_TOKEN) {
		return IfStatement();
	}
	else if (t.GetTokenType() == WHILE_TOKEN) {
		return WhileStatement();
	}
	return NULL;
}

// verify that the next token in the input file is of the
// same type that the parser expects
TokenClass ParserClass::Match(TokenType expectedType)
{
	TokenClass currentToken = mScanner->GetNextToken();
	if (currentToken.GetTokenType() != expectedType)
	{
		cerr << "Error in ParserClass::Match. " << endl;
		cerr << "Expected token type " <<
			TokenClass::GetTokenTypeName(expectedType) <<
			", but got type " << currentToken.GetTokenTypeName()
			<< endl;
		exit(1);
	}
	MSG("\tSuccessfully matched Token Type: " <<
		currentToken.GetTokenTypeName() << ". Lexeme: \"" <<
		currentToken.GetLexeme() << "\"");
	return currentToken; // the one we just processed
}

ExpressionNode* ParserClass::Relational()
{
	ExpressionNode* current = PlusMinus();
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == LESS_TOKEN)
	{
		Match(tt);
		current = new LessNode(current, PlusMinus());
	}
	else if (tt == LESSEQUAL_TOKEN)
	{
		Match(tt);
		current = new LessEqualNode(current, PlusMinus());
	}
	else if (tt == GREATER_TOKEN)
	{
		Match(tt);
		current = new GreaterNode(current, PlusMinus());
	}
	else if (tt == GREATEREQUAL_TOKEN)
	{
		Match(tt);
		current = new GreaterEqualNode(current, PlusMinus());
	}
	else if (tt == EQUAL_TOKEN)
	{
		Match(tt);
		current = new EqualNode(current, PlusMinus());
	}
	else if (tt == NOTEQUAL_TOKEN)
	{
		Match(tt);
		current = new NotEqualNode(current, PlusMinus());
	}
	return current;
}

ExpressionNode* ParserClass::PlusMinus()
{
	ExpressionNode* current = TimesDivide();
	while (true)
	{
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		//cout << mScanner->PeekNextToken() << endl;
		if (tt == PLUS_TOKEN)
		{
			Match(tt);
			current = new PlusNode(current, TimesDivide());
		}
		else if (tt == MINUS_TOKEN)
		{
			Match(tt);
			current = new MinusNode(current, TimesDivide());
		}
		else
		{
			return current;
		}
	}
}

ExpressionNode* ParserClass::TimesDivide()
{
	ExpressionNode* current = Factor();
	while (true)
	{
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == TIMES_TOKEN) {
			Match(tt);
			current = new TimesNode(current, Factor());
		}
		else if (tt == DIVIDE_TOKEN) {
			Match(tt);
			current = new DivideNode(current, Factor());
		}
		return current;
	}
}

ExpressionNode* ParserClass::And()
{
	ExpressionNode* current = Relational();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == AND) {
			Match(tt);
			current = new AndNode(current, Relational());
		}
		return current;
	}
}

ExpressionNode* ParserClass::Or()
{
	ExpressionNode* current = And();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == OR) {
			Match(tt);
			current = new OrNode(current, And());
		}
		return current;
	}
}

ExpressionNode* ParserClass::Factor()
{
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == IDENTIFIER_TOKEN) {
		return Identifier();
	}
	else if (tt == INTEGER_TOKEN) {
		return Integer();
	}
	else if (tt == LPAREN_TOKEN) {
		Match(tt);
		return Expression();
		Match(RPAREN_TOKEN);
	}
	else {
		MSG("This isn't a valid expression");
		return NULL;
	}
}

IdentifierNode* ParserClass::Identifier()
{
	TokenClass tc = Match(IDENTIFIER_TOKEN);
	string lexeme = tc.GetLexeme();
	IdentifierNode* in = new IdentifierNode(lexeme, mSymbolTable);
	return in;
}

IntegerNode* ParserClass::Integer()
{
	TokenClass tc = Match(INTEGER_TOKEN);
	int lexeme = atoi(tc.GetLexeme().c_str());
	IntegerNode* in = new IntegerNode(lexeme);
	return in;
}

DeclarationStatementNode* ParserClass::DeclarationStatement()
{
	Match(INT_TOKEN);
	IdentifierNode* in = Identifier();
	DeclarationStatementNode* dsn = new DeclarationStatementNode(in);
	Match(SEMICOLON_TOKEN);
	return dsn;
}

StatementNode* ParserClass::AssignmentStatement()
{
	IdentifierNode* in = Identifier();
	if (mScanner->PeekNextToken().GetTokenType() == ASSIGNMENT_TOKEN) {
		Match(ASSIGNMENT_TOKEN);
		ExpressionNode* en = Expression();
		Match(SEMICOLON_TOKEN);
		AssignmentStatementNode* an = new AssignmentStatementNode(in, en);
		return an;
	}
	else if (mScanner->PeekNextToken().GetTokenType() == PLUS_EQUAL_TOKEN) {
		Match(PLUS_EQUAL_TOKEN);
		ExpressionNode* en = Expression();
		Match(SEMICOLON_TOKEN);
		PlusEqualNode* pn = new PlusEqualNode(in, en);
		return pn;
	}

	else if (mScanner->PeekNextToken().GetTokenType() == MINUS_EQUAL_TOKEN) {
		Match(MINUS_EQUAL_TOKEN);
		ExpressionNode* en = Expression();
		Match(SEMICOLON_TOKEN);
		MinusEqualNode* pn = new MinusEqualNode(in, en);
		return pn;
	}
}

CoutStatementNode* ParserClass::CoutStatement()
{
	Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	ExpressionNode* en = Expression();
	CoutStatementNode* cn = new CoutStatementNode();
	cn->AddExpression(en);
	if (mScanner->PeekNextToken().GetTokenType() == INSERTION_TOKEN) {
		do {
			Match(INSERTION_TOKEN);
			if (mScanner->PeekNextToken().GetTokenType() == ENDL_TOKEN) {
				Match(ENDL_TOKEN);
			}
			else {
				ExpressionNode* en = Expression();
				cn->AddExpression(en);
			}
		} while (mScanner->PeekNextToken().GetTokenType() == INSERTION_TOKEN);
	}
	Match(SEMICOLON_TOKEN);
	return cn;
}

IfStatementNode* ParserClass::IfStatement()
{
	Match(IF_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* en = Expression();
	Match(RPAREN_TOKEN);
	StatementNode* sn = Statement();
	IfStatementNode* ifn = new IfStatementNode(en, sn);
	return ifn;
}

WhileStatementNode* ParserClass::WhileStatement()
{
	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* en = Expression();
	Match(RPAREN_TOKEN);
	StatementNode* sn = Statement();
	WhileStatementNode* whileNode = new WhileStatementNode(en, sn);
	return whileNode;
}

ExpressionNode* ParserClass::Expression()
{
	return Relational();
}

