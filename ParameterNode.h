/*parameterNode is designed for parsing and obtaining data from data files.It is not implemented yet, but it supports further development

*/
#pragma once
#include <string>
using namespace std;

class CParameterNode
{
public:
	CParameterNode(void);
	CParameterNode(string);
	~CParameterNode(void);


private:
	const string mName;
};

