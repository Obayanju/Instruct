#include "Scanner.h"

ScannerClass::ScannerClass(string str)
	:mFin(str), mLineNumber(1)
{
	if (!mFin) { 
		cerr << "Can't open input file!";
		exit(1);
	}
}

//ScannerClass::~ScannerClass()
//{
//	mFin.close();
//}

TokenClass ScannerClass::GetNextToken()
{
	StateMachineClass stateMachine;
	MachineState current = START_STATE;
	TokenType correspondingTokenType;
	string lexeme;
	char c;
	do {
		c = mFin.get();
		if (c == '\n') mLineNumber += 1;
		lexeme += c;
		current = stateMachine.UpdateState(c, correspondingTokenType);
		if (current == START_STATE || current == EOF_STATE) lexeme = "";
	} while (current != CANTMOVE_STATE);
	if (correspondingTokenType == BAD_TOKEN) { 
		cout << "unrecognized character " << lexeme << endl;
		exit(1); 
	}
	if (c == '\n') mLineNumber--;
	if (lexeme.length() != 1) lexeme.erase(lexeme.size() - 1);
	mFin.unget();
	TokenClass tc = TokenClass(correspondingTokenType, lexeme);
	tc.CheckReserved();
	return tc;
}

TokenClass ScannerClass::PeekNextToken()
{
	int currentLine = GetLineNumber();
	char filePos = mFin.tellg();
	TokenClass tc = GetNextToken();
	if (!mFin) // if we triggered EOF, then seekg doesn't work
		mFin.clear(); // unless we first clear()
	mFin.seekg(filePos);
	mLineNumber = currentLine;
	return tc;
}

int ScannerClass::GetLineNumber()
{
	return mLineNumber;
}
