#include "Symbol.h"
#include <iostream>

using namespace std;

// returns true if <s> is already in the symbol table.
bool SymbolTableClass::Exists(const std::string& s)
{
	for (int i = 0; i < mTable.size(); i++) {
		if (s == mTable[i].mLabel) return true;
	}
	return false;
}

void SymbolTableClass::AddEntry(const std::string& s)
{
	if (Exists(s)) exit(1);
	mTable.push_back({ s,0 });
	/*bool found = false;
	for (int i = 0; i < mTable.size(); i++) {
		if (s == mTable[i].mLabel) found = true;
	}
	
	if (!found) {
		Variable v;
		v.mLabel = s;
		mTable.push_back(v);
	}
	else {
		cerr << "The variable " << s << " already exists." << endl;
		exit(0);
	}*/
}

// returns the current value of variable <s>, when
// interpreting. Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
int SymbolTableClass::GetValue(const std::string& s)
{
	bool found = false;
	for (int i = 0; i < mTable.size(); i++) {
		if (mTable[i].mLabel == s) {
			found = true;
			return mTable[i].mValue;
		}
	}

	if (!found) {
		cerr << "Cannot getvalue. The variable " << s << " does not exist" << endl;
		exit(0);
	}
}

// sets variable <s> to the given value, when interpreting.
// Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
void SymbolTableClass::SetValue(const std::string& s, int v)
{
	bool found = false;
	for (int i = 0; i < mTable.size(); i++) {
		if (mTable[i].mLabel == s) {
			found = true;
			mTable[i].mValue = v;
		}
	}

	if (!found) {
		cerr << "Cannot setvalue. The variable " << s << " does not exist" << endl;
		exit(0);
	}
}

int SymbolTableClass::GetIndex(const std::string& s)
{
	bool found = false;
	for (int i = 0; i < mTable.size(); i++) {
		if (mTable[i].mLabel == s) {
			found = true;
			return i;
		}
	}
	if (!found) {
		cerr << "Cannot getindex. " <<  s << " does not exist" << endl;
		exit(0);
		return -1;
	}
}

// returns the current number of variables in the symbol
// table.
int SymbolTableClass::GetCount()
{
	return mTable.size();
}
