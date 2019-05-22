#include "const_reader.h"
#include "const_Ex.h"
#include <iostream>
#include <cmath>

enum SYMBOLS { DIG, EXP, POINT, SIGN, OTHER, END };


SYMBOLS transliterator(const char& ch)
{
	if (ch >= '0' && ch <= '9') return DIG;
    if (ch == 'E' || ch == 'e') return EXP;
	if (ch == '.')				return POINT;
	if (ch == '+' || ch == '-') return SIGN;
	if (ch == '\0' || ch == '\n') return END;

	return OTHER;
}


const_reader::const_reader()
{
	ptr = &const_reader::A0;
	str = "";
}

void const_reader::setWord(std::string str_)
{
	str = str_;
	ptr = &const_reader::A0;
}

bool const_reader::Lets_Go(double& result_)
{

	for (size_t i = 0; i < str.size(); i++)
		(this->*ptr)(str[i]);

	if (ptr == &const_reader::A0) throw new no_word_ex();

	if (ptr == &const_reader::A3) throw new ConstEX14();

	if (ptr == &const_reader::A4) throw new ConstEX15();

	if (ptr == &const_reader::A6) throw new ConstEX16();

	if (ptr == &const_reader::A1)	result_ = r_CH;

	if (ptr == &const_reader::A2)	result_ = r_CH / pow(10, r_S);
	
	if (ptr == &const_reader::A5)
		result_ = r_CH * pow(10, r_P + (negtv == 1) ? -r_S : r_S );
		
	std::cout << "const = " << result_ << std::endl;
	return true;
}

void const_reader::A0(const char& ch)
{
	switch (transliterator(ch))
	{
	case DIG:
		r_CH = ch - '0';
		ptr = &const_reader::A1;
		break;

	case EXP: throw new ConstEX12();
	case POINT:
		r_S = 0;
		ptr = &const_reader::A6;
		break;

	case SIGN: throw new ConstEX2();

	default: throw new ConstEX1();
	}

}

void const_reader::A1(const char & ch)
{
	switch (transliterator(ch))
	{
	case DIG: r_CH = r_CH*10 + (ch - '0');
		break;

	case EXP:
		r_S = 0; 
		ptr = &const_reader::A3;
		break;

	case POINT:
		r_S = 0;
		ptr = &const_reader::A2;
		break;

	case SIGN: throw new ConstEX3();

	default: throw new ConstEX1();
	}
}

void const_reader::A2(const char & ch)
{
	switch (transliterator(ch))
	{
	case DIG:
		r_CH = r_CH * 10 + (ch - '0');
		r_S++;
		break;

	case EXP: ptr = &const_reader::A3;
		break;

	case POINT: throw new ConstEX6();

	case SIGN: throw new ConstEX4();

	default: throw new ConstEX1();
	}
}

void const_reader::A3(const char & ch)
{
	switch (transliterator(ch))
	{
	case DIG:
		r_P = ch - '0';
		negtv = true;
		ptr = &const_reader::A5;
		break;

	case EXP: throw new ConstEX11();

	case POINT: throw new ConstEX9();

	case SIGN:
		negtv = (ch == '+');
		ptr = &const_reader::A4;
		break;

	default: throw new ConstEX1();
	}
}

void const_reader::A4(const char & ch)
{
	switch (transliterator(ch))
	{
	case DIG:
		r_P = ch - '0';
		ptr = &const_reader::A5;
		break;

	case EXP: throw new ConstEX11();

	case POINT: throw new ConstEX6();

	case SIGN: throw new ConstEX5();

	default: throw new ConstEX1();
	}
}

void const_reader::A5(const char & ch)
{
	switch (transliterator(ch))
	{
	case DIG:
		r_P = r_P * 10 + (ch - '0');
		ptr = &const_reader::A5;
		break;

	case EXP: throw new ConstEX7();

	case POINT: throw new ConstEX8();

	case SIGN: throw new ConstEX5();

	default: throw new ConstEX1();
	}
}

void const_reader::A6(const char & ch)
{
	switch (transliterator(ch))
	{
	case DIG:
		r_CH = ch - '0';
		r_S++;
		ptr = &const_reader::A2;
		break;

	case EXP: throw new ConstEX7();

	case POINT: throw new ConstEX6();

	case SIGN: throw new ConstEX4();

	default: throw new ConstEX1();
	}
}