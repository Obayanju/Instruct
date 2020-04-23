#pragma once
#ifndef TOKEN
#define TOKEN

#include <string>
#include <iostream>
using namespace std;

// assigns all token types to integers
enum TokenType {
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, IF_TOKEN, WHILE_TOKEN,
	// Relational Operators:
	LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN,
	EQUAL_TOKEN, NOTEQUAL_TOKEN,
	// Other Operators:
	INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN,
	TIMES_TOKEN, DIVIDE_TOKEN,
	// Other Characters:
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN,
	RCURLY_TOKEN,
	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN,
	BAD_TOKEN, EOF_TOKEN, AND, OR
};

// IMPORTANT: The list above and the list below MUST be kept in sync.
const string gTokenTypeNames[] = {
"VOID", "MAIN", "INT", "COUT", "IF", "WHILE",
"LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL",
"NOTEQUAL",
"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE",
"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
"IDENTIFIER", "INTEGER",
"BAD", "ENDFILE"
};


class TokenClass
{
private:
	TokenType mType;
	string mLexeme;
public:
	TokenClass();
	TokenClass(TokenType type, const string& lexeme);
	TokenType GetTokenType() const { return mType; }
	const string& GetTokenTypeName() const
	{
		return gTokenTypeNames[mType];
	}
	string GetLexeme() const { return mLexeme; }
	void CheckReserved();
	static const string& GetTokenTypeName(TokenType type)
	{
		return gTokenTypeNames[type];
	}
};

ostream& operator<<(ostream& out, const TokenClass& tc);

#endif //TOKEN