#include "Token.h"
#include <algorithm>
#include <iostream>
using namespace std;

int case_insensitive_match(string s1, string s2) {
	//convert s1 and s2 into lower case strings
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	if (s1.compare(s2) == 0)
		return 1; //The strings are same
	return 0; //not matched
}

TokenClass::TokenClass()
{
}


TokenClass::TokenClass(TokenType type, const string& lexeme)
	:mType(type), mLexeme(lexeme)
{
}

void TokenClass::CheckReserved()
{
	for (int i = 0; i <= EOF_TOKEN; i++) {
		if (case_insensitive_match(mLexeme, gTokenTypeNames[i])) {
			mType = static_cast<TokenType>(i);
		}
	}
	/*if (mLexeme == "void") mType = VOID_TOKEN;
	else if (mLexeme == "main") mType = MAIN_TOKEN;
	else if (mLexeme == "int") mType = INT_TOKEN;
	else if (mLexeme == "cout") mType = COUT_TOKEN;*/
}

ostream& operator<<(ostream& out, const TokenClass& tc)
{
	cout << tc.GetTokenTypeName(tc.GetTokenType()) << " " << tc.GetLexeme() << endl;
	return out;
}
