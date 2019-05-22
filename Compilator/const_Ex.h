#pragma once

#include <stdexcept>
#include <string>
class ConstEX : public std::exception
{
public:
	ConstEX() { msg = "�������� ���������:\n"; }
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
		msg += "���������� ������ �� �������� � ������� ���������";
	}
};

class ConstEX2 : public ConstEX
{
public:
	ConstEX2() : ConstEX()
	{
		msg += "������ �������� �� ����� ���� ���� �������\n";
	}
	
};

class ConstEX3 : public ConstEX
{
public:
	ConstEX3() : ConstEX()
	{
		msg +="� ����� ����� �� ����� �������������� ���� �������\n";
	}
	
};

class ConstEX4 : public ConstEX
{
public:
	ConstEX4() : ConstEX()
	{
		msg += "� ������ ������� ����� �� ����� ������ ���� �������\n";
	}
	
};

class ConstEX5 : public ConstEX
{
public:
	ConstEX5() : ConstEX()
	{
		msg += "� ��������� ����������� ��� ����� �������\n";
	}
};

class ConstEX6 : public ConstEX
{
public:
	ConstEX6() : ConstEX()
	{
		msg += "� ��������� ����������� ��� �����\n";;
	}
	
};

class ConstEX7 : public ConstEX
{
public:
	ConstEX7() : ConstEX()
	{
		msg += "������� ������� �������� 'E'\n";
	}
	
};

class ConstEX8 : public ConstEX
{
public:
	ConstEX8() : ConstEX()
	{
		msg += "� �������� ������� ����������� �����\n";
	}
	
};

class ConstEX9 : public ConstEX
{
public:
	ConstEX9() : ConstEX()
	{
		msg += "����� 'E' ����������� �����\n";
	}
	
};

class ConstEX10 : public ConstEX
{
public:
	ConstEX10() : ConstEX()
	{
		msg += "����� ����� ������� ��������� �����\n";
	}
	
};

class ConstEX11 : public ConstEX
{
public:
	ConstEX11() : ConstEX()
	{
		msg += "� ��������� ��� 'E'\n";
	}
};

class ConstEX12 : public ConstEX
{
public:
	ConstEX12() : ConstEX()
	{
		msg += "��������� ���������� � 'E'\n";
	}
	
};

class no_word_ex : public ConstEX
{
public:
	no_word_ex() : ConstEX()
	{
		msg += "������ ������ ����� ��� ��������\n";
	}
	
};

class ConstEX14 : public ConstEX
{
public:
	ConstEX14() : ConstEX()
	{
		msg += "����������� ������� ����� 'E'\n";
	}
};

class ConstEX15 : public ConstEX
{
public:
	ConstEX15() : ConstEX()
	{
		msg += "����������� ������� ����� ����� �������!\n";
	}
	
};

class ConstEX16 : public ConstEX
{
public:
	ConstEX16() : ConstEX()
	{
		msg += "��������� �� ����� �������� ������ �� �����!\n";
	}
};
