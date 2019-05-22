#pragma once
#include <stdexcept>
class OperatorEx : public std::exception
{
public:
	OperatorEx(std::string msg_ = "") : msg("Operator Error!")
	{
		msg += ("\n" + msg_);
	}
protected:
	std::string msg;
};
class ConstEx : public std::exception
{
public:
	ConstEx() {}
	const char* what() const override
	{
		return "Error in const!";
	}
};

class ExceptA2 : public std::exception
{
public:
	ExceptA2(){}
	const char* what() const override
	{
		return "Error in A2";
	}
};
class ExceptA3 : public std::exception
{
public:
	ExceptA3(){}
	const char* what() const override
	{
		return "Error in A3";
	}
};
class ExceptD1 : public std::exception
{
public:
	ExceptD1(){}
	const char* what() const override
	{
		return "Error in D1";	// глянуть потом
	}
};
class ExceptH1 : public std::exception
{
public:
	ExceptH1(){}
	const char* what() const override
	{
		return "Error in H1"; // Посмотреть потом
	}
};
class ExceptM1 : public std::exception
{
public:
	ExceptM1(){}
	const char* what() const override
	{
		return "Error in M1";
	}
};

class Except1 : public std::exception
{
public:
	Except1() {}
	const char* what() const override
	{
		return "Not found \'metka\' in begining string";
	}
};
class Except2 : public std::exception
{
public:
	Except2(){}
	const char* what() const override
	{
		return "Variable not found after operator!";
	}
};
class Except3 : public std::exception
{
public:
	Except3(){}
	const char* what() const override
	{
		return "Error: point after variable!";
	}
};
class Except4 : public std::exception
{
public:
	Except4(){}
	const char* what() const override
	{
		return "2 point successively";
	}
};
class Except5 : public std::exception
{
public:
	Except5(){}
	const char* what() const override
	{
		return "Not found number of string after operator";
	}
};
class Except6 : public std::exception
{
public:
	Except6(){}
	const char* what() const override
	{
		return "Error in number string";
	}
};
class Except7 : public std::exception
{
public:
	Except7(){}
	const char* what() const override
	{
		return "Variable not found after operator";
	}
};
class Except8 : public std::exception
{
public:
	Except8(){}
	const char* what() const override
	{
		return "Error in variable after operator";
	}
};
class Except9 : public std::exception
{
public:
	Except9(){}
	const char* what() const override
	{
		return "Not found \'=\' after variable";
	}
};
