#pragma once
#include <iostream>
#include <fstream>
#include "Token.h"
#include "StateMachine.h"

class ScannerClass {
public:
	ScannerClass(string in);
	//~ScannerClass();
	TokenClass GetNextToken();
	TokenClass PeekNextToken();
	int GetLineNumber();
private:
	ifstream mFin;
	int mLineNumber;
};
