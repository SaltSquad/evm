#pragma once

#include <stdexcept>
#include <string>
class ConstEX : public std::exception
{
public:
	ConstEX() { msg = "Неверная константа:\n"; }
	const char* what() const throw() override
	{
		return msg.c_str();
	}
protected:
	std::string msg;
};

class ConstEX1 : public ConstEX
{
public:
	ConstEX1() : ConstEX()
	{
		msg += "Встретился символ не входящий в алфавит константы";
	}
};

class ConstEX2 : public ConstEX
{
public:
	ConstEX2() : ConstEX()
	{
		msg += "Первым символом не может быть знак порядка\n";
	}
	
};

class ConstEX3 : public ConstEX
{
public:
	ConstEX3() : ConstEX()
	{
		msg +="В целой части не может присутствовать знак порядка\n";
	}
	
};

class ConstEX4 : public ConstEX
{
public:
	ConstEX4() : ConstEX()
	{
		msg += "В начале дробной части не может стоять знак порядка\n";
	}
	
};

class ConstEX5 : public ConstEX
{
public:
	ConstEX5() : ConstEX()
	{
		msg += "В константе встречаются два знака порядка\n";
	}
};

class ConstEX6 : public ConstEX
{
public:
	ConstEX6() : ConstEX()
	{
		msg += "В константе встречаются две точки\n";;
	}
	
};

class ConstEX7 : public ConstEX
{
public:
	ConstEX7() : ConstEX()
	{
		msg += "Регистр порядка содержит 'E'\n";
	}
	
};

class ConstEX8 : public ConstEX
{
public:
	ConstEX8() : ConstEX()
	{
		msg += "В регистре порядка встретилась точка\n";
	}
	
};

class ConstEX9 : public ConstEX
{
public:
	ConstEX9() : ConstEX()
	{
		msg += "После 'E' встретилась точка\n";
	}
	
};

class ConstEX10 : public ConstEX
{
public:
	ConstEX10() : ConstEX()
	{
		msg += "После знака порядка встретили точку\n";
	}
	
};

class ConstEX11 : public ConstEX
{
public:
	ConstEX11() : ConstEX()
	{
		msg += "В константе две 'E'\n";
	}
};

class ConstEX12 : public ConstEX
{
public:
	ConstEX12() : ConstEX()
	{
		msg += "Константа начинается с 'E'\n";
	}
	
};

class no_word_ex : public ConstEX
{
public:
	no_word_ex() : ConstEX()
	{
		msg += "Подано пустое слово для проверки\n";
	}
	
};

class ConstEX14 : public ConstEX
{
public:
	ConstEX14() : ConstEX()
	{
		msg += "Отсутствует порядок после 'E'\n";
	}
};

class ConstEX15 : public ConstEX
{
public:
	ConstEX15() : ConstEX()
	{
		msg += "Отсутствует порядок после знака порядка!\n";
	}
	
};

class ConstEX16 : public ConstEX
{
public:
	ConstEX16() : ConstEX()
	{
		msg += "Константа не может состоять только из точки!\n";
	}
};
