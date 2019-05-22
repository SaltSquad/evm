#include "rlib.h"
#include <algorithm>
#include <stack>
using namespace std;

bool digit(const char &c)
{
	return c >= '0' && c <= '9';
}

bool litter(const char &c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool dig_or_lit(const char& c)
{
	return	digit(c) + litter(c);
		
}
bool isNatural(const std::string & str)
{
	size_t N = str.size();

	if (N != 0)
	{
		for (size_t i = 0; i < N; i++)
			if (!digit(str[i])) return false;

		return true;
	}
	else
		return false;

}
bool isVar(const std::string& str)
{
	if (!digit(str.front()) && !str.empty())
	{
		string::const_iterator frst = str.begin();
		string::const_iterator lst = str.end();

		size_t varSym = count_if(frst, lst, dig_or_lit);	/*
			кол.-во букв и цифр в предполагаемом идентификаторе
		*/

		return (varSym == str.size());
		
	}
	return false;
}

size_t get_priority(const string& op_)
{
	//const char* opeations = "*/%+-<=&|";
	const string operations[9] =
	{
		"*/%", "+-", "<>", ">=<=",
		"=", "!=", "&", "|", "("
	};

	size_t i = 0;
	while (operations[i].find(op_) == -1) i++;

	return i;
}

string pop_front(string& line_)
{
	size_t i = 0;
	while (line_[i] == ' ' || line_[i] == '\t') i++;
	
	line_.erase(0, i);

	string word;
	if (line_.size() > 1) // двусимв. операторы
	{
		
		const string* frs = op_dual;
		const string* lst = op_dual + g_dualOp;

		const string* it = find(frs, lst, line_.substr(0, 2));

		if (it != lst)
		{
			word = *it;
			line_.erase(0, 2);

			return word;
		}
	}
	
	if (op_single.find(line_[0]) != -1)	/*
		если в начале односимв. слово*/
		i = 1;
	else
		for (i = 0; line_[i] && op_single.find(line_[i]) == -1; i++);

	word = line_.substr(0, i);
	line_.erase(0, i);

	return word;
}
