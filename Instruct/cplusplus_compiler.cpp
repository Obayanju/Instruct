#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"
#include "Debug.h"
#include "Parser.h"

using namespace std;
   
void CodeAndExecute(string inputFile)
{
	// Create scanner, symbol table, and parser objects.
	ScannerClass scanner(inputFile);
	SymbolTableClass symbolTable;
	ParserClass parser(&symbolTable, &scanner);
	// Do the parsing, which results in a parse tree.
	StartNode* root = parser.Start();
	// Create the machine code instructions from the parse tree
	InstructionsClass machineCode;
	root->Code(machineCode);
	machineCode.Finish();
	machineCode.PrintAllMachineCodes();
	// Execute the machine code instructions previously created
	machineCode.Execute();
	// cleanup recursively
	delete root;
}

int main()
{
	CodeAndExecute("source_code.txt");

	/*  Parser without output Test */
	/*SymbolTableClass sTable;
	ScannerClass scanner("source_code.txt");
	ParserClass parser = ParserClass(&sTable, &scanner);
	parser.Start();

	return 0;*/

	/*
	ScannerClass scanner("source_code.txt");
	while (true) {
		TokenClass tc = scanner.GetNextToken();
		cout << scanner.GetLineNumber() << " ";
		cout << tc << endl;
		if (tc.GetTokenType() == EOF_TOKEN) break;
	}
	*/
	/* 
	SymbolTableClass sTable;
	sTable.AddEntry("sum");
	sTable.SetValue("sum", 10);
	sTable.AddEntry("prod");
	sTable.SetValue("prod", 100);
	sTable.GetIndex("div");
	cout << sTable.GetValue("sum") << endl;
	cout << sTable.GetIndex("prod") << endl; 
	*/


	/* TEST 1 */

	//SymbolTableClass st;

	//// int sum
	//IdentifierNode* sum = new IdentifierNode("sum", &st);
	//DeclarationStatementNode* dsn = new DeclarationStatementNode(sum);

	//// sum = 35 + 400
	//IntegerNode* left = new IntegerNode(35);
	//IntegerNode* right = new IntegerNode(400);
	//PlusNode* pN1 = new PlusNode(left, right);
	//AssignmentStatementNode* asn = new AssignmentStatementNode(sum, pN1);
	////cout << sum
	//CoutStatementNode* csn = new CoutStatementNode(sum);
	//
	//StatementGroupNode* sgn = new StatementGroupNode();
	//sgn->AddStatement(csn);
	//BlockNode* bn = new BlockNode(sgn);
	//ProgramNode* pn = new ProgramNode(bn);
	//StartNode* s = new StartNode(pn);
	//delete(s);

	/* TEST 2 */

	//SymbolTableClass st;

	//IntegerNode* intN3 = new IntegerNode(15);
	//IntegerNode* intN4 = new IntegerNode(10);
	//IntegerNode* intN5 = new IntegerNode(10);
	//IntegerNode* intN6 = new IntegerNode(5);
	//IntegerNode* intN7 = new IntegerNode(20);
	//IntegerNode* intN8 = new IntegerNode(2);
	//IntegerNode* intN9 = new IntegerNode(5);
	//IntegerNode* intN10 = new IntegerNode(6);


	//PlusNode* plusN = new PlusNode(intN3, intN4); // 25
	//MinusNode* minusN = new MinusNode(intN5, intN6); // 5
	//DivideNode* divideN = new DivideNode(intN7, intN8); // 10
	//TimesNode* timesN = new TimesNode(intN9, intN10); // 30

	//cout << plusN->Evaluate() << " " << minusN->Evaluate() << " " << divideN->Evaluate() << " " << timesN->Evaluate() << endl;


	//IdentifierNode* idN = new IdentifierNode("x", &st);
	//AssignmentStatementNode* asn = new AssignmentStatementNode(idN, plusN);
	//IdentifierNode* idN1 = new IdentifierNode("y", &st);
	//AssignmentStatementNode* asn2 = new AssignmentStatementNode(idN1, minusN);
	//IdentifierNode* idN2 = new IdentifierNode("z", &st);
	//AssignmentStatementNode* asn3 = new AssignmentStatementNode(idN2, divideN);
	//IdentifierNode* mult = new IdentifierNode("mult", &st);
	//AssignmentStatementNode* asn4 = new AssignmentStatementNode(mult, timesN);

	//StatementGroupNode* sgn = new StatementGroupNode();
	//sgn->AddStatement(asn);
	//sgn->AddStatement(asn2);
	//sgn->AddStatement(asn3);
	//sgn->AddStatement(asn4);
	//BlockNode* bn = new BlockNode(sgn);
	//ProgramNode* pn = new ProgramNode(bn);
	//StartNode* s = new StartNode(pn);
	//delete(s);
}
