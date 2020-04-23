#pragma once
#include <vector>
#include <string>
using namespace std;
/*
	Used to store variables for interpreting and compiling
*/
class SymbolTableClass {
public:
	struct Variable {
		string mLabel;
		int mValue;
	};
	bool Exists(const std::string& s);
	void AddEntry(const std::string& s);
	int GetValue(const std::string& s);
	void SetValue(const std::string& s, int v);
	int GetIndex(const std::string& s);
	int GetCount();
	vector<Variable> mTable;
};
