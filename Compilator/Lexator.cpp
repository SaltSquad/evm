#include "Lexator.h"
#include <fstream>
#include <functional>
#include "except.h"
#include <iostream>
using namespace std;
size_t rconvert(const string* begin, size_t N, const string& target)
{
	for (size_t i = 0; i < N; i++)
		if (begin[i] == target) return i;

	return -1;
}

void Lexator::start(const char* prog,
	const char* error, const char* rez)
{
	ifstream in(prog);
	ofstream er_out(error);
	ofstream result(rez);

	if (!(in.is_open() && er_out.is_open() && result.is_open()))
		exit(1);
	
	size_t num = 1;
	States st;
	do {
		getline(in, str);

		try
		{
			size_t N = str.size();

			for (size_t i = 0; i <= N; i++)	// захватываем \n
			{
				translit(str[i]);
				(this->*state[RST][RK])();
			}
		}
		catch (exception e)
		{
			er_out << "Error in line: " << num << endl
				<< e.what() << endl;
		}

		/*20 if a>b go to 40

30 fo i=1 to 5

50 let = 3.25

go to 80

70 next

90 d=3*a23-4

100 let z c5

110 let m1=(35+x)/75.2)

120 let t1=15.2+02

130 for j=1 do 5 step 2

140 let f=f*j

150 next j*/
		num++;
	} while (!in.eof());
	
	/*	TODO: Обработать:
	 *	Если файл закончился а состояние не EXIT*/

	int eq = 20;

	result << "\tSTRING TABLE" << endl <<
		string(eq, '=') << endl;
	//TODO:
	result << TS << endl;
	result << string(eq, '=') << endl;

	cout << TS << endl;
	cout << string(eq, '=') << endl;	// del

	result << "\tOPERAND TABLE" << endl <<
		string(eq, '=') << endl;
	//TODO:
	result << TO << endl;
	result << string(eq, '=') << endl;

	cout << TO << endl;
	cout << string(eq, '=') << endl;	// del

	result << "\tLEXEM TABLE" << endl <<
		string(eq, '=') << endl;
	//TODO:
	for (Lexem x : TL) {
		result << x << endl;
		cout << x << endl;
	}
	result << string(eq, '=') << endl;
	cout << string(eq, '=') << endl;
	er_out.close();
	result.close();
	in.close();
}

void Lexator::translit(char c)
{
	char sym = toupper(c);

	if (sym >= 'A' && sym <= 'Z'){
		RK = litter;
		RZN = sym - 'A' + 1;
		return;
	}

	if (sym >= '0' && sym <= '9'){
		RK = digit;
		RZN = sym - '0';
		return;
	}

	size_t type = string("+-*/^").find(sym);
	if (type != -1){
		RK = ar_op; RZN = type;
		return;
	}
	
	type = string("=<>").find(sym);
	if (type != -1)
	{
		RK = cmp_op; RZN = type;
		return;
	}

	switch (sym)
	{
	case '(': RK = lscr;
		break;
	case ')': RK = rscr;
		break;

	case '.': RK = point;
		break;
	case ' ': RK = space;
		break;
	case '\0': RK = Eos;
		break;
	}
}
Lexator::Lexator()
{
	init();
	RST = A1;
	RCH = RZ = RP = RS = 0;
	NTO = 287;
}

void Lexator::init()
{
	/*Базисный вектор*/
	for (size_t i = 0; i < 26; i++)			
		ROBarr[i] = 0;							 
	ROBarr[4] = 1;	ROBarr[8] = 11;				 
	ROBarr[5] = 3;	ROBarr[11] = 12;				
	ROBarr[6] = 5;	ROBarr[13] = 14;				
	ROBarr[17] = 17; ROBarr[18] = 23; ROBarr[19] = 26;

	/*Вектор альтернатив*/
	size_t k = 0;	
	TOb[k++] = 14;	TOb[k++] = 4;
	TOb[k++] = 15;	TOb[k++] = 18;
	TOb[k++] = 15;	TOb[k++] = 20;
	TOb[k++] = 15;	TOb[k++] = 19;
	TOb[k++] = 21;	TOb[k++] = 2;
	TOb[k++] = 6;	TOb[k++] = 5;
	TOb[k++] = 20;	TOb[k++] = 5;
	TOb[k++] = 24;	TOb[k++] = 20;
	TOb[k++] = 5;	TOb[k++] = 20;
	TOb[k++] = 21;	TOb[k++] = 18;
	TOb[k++] = 14;	TOb[k++] = 13;
	TOb[k++] = 20;	TOb[k++] = 5;
	TOb[k++] = 16;	TOb[k] = 15;

	/*Таблица переходов*/
	state[A1][litter] = &Lexator::_A1Ex;
	state[A1][digit] = &Lexator::_E2a;
	state[A1][ar_op] = &Lexator::_A1Ex;
	state[A1][cmp_op] = &Lexator::_A1Ex;
	state[A1][lscr] = &Lexator::_A1Ex;
	state[A1][rscr] = &Lexator::_A1Ex;
	state[A1][point] = &Lexator::_A1Ex;
	state[A1][space] = &Lexator::_A1;
	state[A1][Eos] = &Lexator::_A1;
	state[A1][Eof] = &Lexator::_EXIT1;

	state[A2][litter] = &Lexator::_c2a;
	state[A2][digit] = &Lexator::_D1a;
	state[A2][ar_op] = &Lexator::_A2a;
	state[A2][cmp_op] = &Lexator::_H1a;
	state[A2][lscr] = &Lexator::_A2h;
	state[A2][rscr] = &Lexator::_A3b;
	state[A2][point] = &Lexator::_D6;
	state[A2][space] = &Lexator::_A2;
	state[A2][Eos] = &Lexator::_A1;
	state[A2][Eof] = &Lexator::_EXIT1;

	state[A3][litter] = &Lexator::_B1a;
	state[A3][digit] = &Lexator::_D1a;
	state[A3][ar_op] = &Lexator::_A2a;
	state[A3][cmp_op] = &Lexator::_H1a;
	state[A3][lscr] = &Lexator::_A2h;
	state[A3][rscr] = &Lexator::_A3b;
	state[A3][point] = &Lexator::_D6;
	state[A3][space] = &Lexator::_A2;
	state[A3][Eos] = &Lexator::_A1;
	state[A3][Eof] = &Lexator::_EXIT1;

	state[B1][litter] = &Lexator::_M1;
	state[B1][digit] = &Lexator::_B1Ex;
	state[B1][ar_op] = &Lexator::_B1Ex;
	state[B1][cmp_op] = &Lexator::_B1Ex;
	state[B1][lscr] = &Lexator::_B1Ex;
	state[B1][rscr] = &Lexator::_B1Ex;
	state[B1][point] = &Lexator::_B1Ex;
	state[B1][space] = &Lexator::_B1;
	state[B1][Eos] = &Lexator::_B1Ex;
	state[B1][Eof] = &Lexator::_B1Ex;

	state[C1][litter] = &Lexator::_c2d;
	state[C1][digit] = &Lexator::_C1Ex;
	state[C1][ar_op] = &Lexator::_C1Ex;
	state[C1][cmp_op] = &Lexator::_C1Ex;
	state[C1][lscr] = &Lexator::_C1Ex;
	state[C1][rscr] = &Lexator::_C1Ex;
	state[C1][point] = &Lexator::_C1Ex;
	state[C1][space] = &Lexator::_C1;
	state[C1][Eos] = &Lexator::_C1Ex;
	state[C1][Eof] = &Lexator::_EXIT3;

	state[C2][litter] = &Lexator::_B1b;
	state[C2][digit] = &Lexator::_A3a;
	state[C2][ar_op] = &Lexator::_A2g;
	state[C2][cmp_op] = &Lexator::_H1b;
	state[C2][lscr] = &Lexator::_A2k;
	state[C2][rscr] = &Lexator::_A3c;
	state[C2][point] = &Lexator::_C2Ex;
	state[C2][space] = &Lexator::_c2;
	state[C2][Eos] = &Lexator::_A1a;
	state[C2][Eof] = &Lexator::_EXIT4;

	state[D1][litter] = &Lexator::_M2;
	state[D1][digit] = &Lexator::_D1b;
	state[D1][ar_op] = &Lexator::_A2c;
	state[D1][cmp_op] = &Lexator::_H1c;
	state[D1][lscr] = &Lexator::_A2l;
	state[D1][rscr] = &Lexator::_A3d;
	state[D1][point] = &Lexator::_D2c;
	state[D1][space] = &Lexator::_D1;
	state[D1][Eos] = &Lexator::_A1b;
	state[D1][Eof] = &Lexator::_EXIT3;


	state[D2][litter] = &Lexator::_M3;
	state[D2][digit] = &Lexator::_D2a;
	state[D2][ar_op] = &Lexator::_A2d;
	state[D2][cmp_op] = &Lexator::_H1d;
	state[D2][lscr] = &Lexator::_A2m;
	state[D2][rscr] = &Lexator::_A3d;
	state[D2][point] = &Lexator::_D2Ex;
	state[D2][space] = &Lexator::_D2;
	state[D2][Eos] = &Lexator::_A1c;
	state[D2][Eof] = &Lexator::_EXIT4;

	state[D3][litter] = &Lexator::_D36Ex;
	state[D3][digit] = &Lexator::_D5a;
	state[D3][ar_op] = &Lexator::_D4a;
	state[D3][cmp_op] = &Lexator::_D36Ex;
	state[D3][lscr] = &Lexator::_D36Ex;
	state[D3][rscr] = &Lexator::_D36Ex;
	state[D3][point] = &Lexator::_D36Ex;
	state[D3][space] = &Lexator::_D3;
	state[D3][Eos] = &Lexator::_D36Ex;
	state[D3][Eof] = &Lexator::_D36Ex;

	state[D4][litter] = &Lexator::_D36Ex;
	state[D4][digit] = &Lexator::_D5b;
	state[D4][ar_op] = &Lexator::_D36Ex;
	state[D4][cmp_op] = &Lexator::_D36Ex;
	state[D4][lscr] = &Lexator::_D36Ex;
	state[D4][rscr] = &Lexator::_D36Ex;
	state[D4][point] = &Lexator::_D36Ex;
	state[D4][space] = &Lexator::_D4;
	state[D4][Eos] = &Lexator::_D36Ex;
	state[D4][Eof] = &Lexator::_D36Ex;

	state[D5][litter] = &Lexator::_B1c;
	state[D5][digit] = &Lexator::_D5c;
	state[D5][ar_op] = &Lexator::_A2e;
	state[D5][cmp_op] = &Lexator::_H1c;
	state[D5][lscr] = &Lexator::_A2n;
	state[D5][rscr] = &Lexator::_A3f;
	state[D5][point] = &Lexator::_D36Ex;
	state[D5][space] = &Lexator::_D5;
	state[D5][Eos] = &Lexator::_A1d;
	state[D5][Eof] = &Lexator::_EXIT5;

	state[D6][litter] = &Lexator::_D36Ex;
	state[D6][digit] = &Lexator::_D2b;
	state[D6][ar_op] = &Lexator::_D36Ex;
	state[D6][cmp_op] = &Lexator::_D36Ex;
	state[D6][lscr] = &Lexator::_D36Ex;
	state[D6][rscr] = &Lexator::_D36Ex;
	state[D6][point] = &Lexator::_D36Ex;
	state[D6][space] = &Lexator::_D6;
	state[D6][Eos] = &Lexator::_D36Ex;
	state[D6][Eof] = &Lexator::_D36Ex;

	state[E1][litter] = &Lexator::_E1Ex;
	state[E1][digit] = &Lexator::_E2b;
	state[E1][ar_op] = &Lexator::_E1Ex;
	state[E1][cmp_op] = &Lexator::_E1Ex;
	state[E1][lscr] = &Lexator::_E1Ex;
	state[E1][rscr] = &Lexator::_E1Ex;
	state[E1][point] = &Lexator::_E1Ex;
	state[E1][space] = &Lexator::_E1;
	state[E1][Eos] = &Lexator::_E1Ex;
	state[E1][Eof] = &Lexator::_E1Ex;

	state[E2][litter] = &Lexator::_B1e;
	state[E2][digit] = &Lexator::_E2c;
	state[E2][ar_op] = &Lexator::_A2f;
	state[E2][cmp_op] = &Lexator::_H1f;
	state[E2][lscr] = &Lexator::_A2j;
	state[E2][rscr] = &Lexator::_A3g;
	state[E2][point] = &Lexator::_E2Ex;
	state[E2][space] = &Lexator::_E2;
	state[E2][Eos] = &Lexator::_A1e;
	state[E2][Eof] = &Lexator::_E2Ex;

	state[F1][litter] = &Lexator::_F2a;
	state[F1][digit] = &Lexator::_F1Ex;
	state[F1][ar_op] = &Lexator::_F1Ex;
	state[F1][cmp_op] = &Lexator::_F1Ex;
	state[F1][lscr] = &Lexator::_F1Ex;
	state[F1][rscr] = &Lexator::_F1Ex;
	state[F1][point] = &Lexator::_F1Ex;
	state[F1][space] = &Lexator::_F1;
	state[F1][Eos] = &Lexator::_F1Ex;
	state[F1][Eof] = &Lexator::_F1Ex;

	state[F2][litter] = &Lexator::_F2Ex;
	state[F2][digit] = &Lexator::_F3a;
	state[F2][ar_op] = &Lexator::_F2Ex;
	state[F2][cmp_op] = &Lexator::_A2o;
	state[F2][lscr] = &Lexator::_F2Ex;
	state[F2][rscr] = &Lexator::_F2Ex;
	state[F2][point] = &Lexator::_F2Ex;
	state[F2][space] = &Lexator::_F2;
	state[F2][Eos] = &Lexator::_F2Ex;
	state[F2][Eof] = &Lexator::_F2Ex;

	state[F3][litter] = &Lexator::_F3Ex;
	state[F3][digit] = &Lexator::_F3Ex;
	state[F3][ar_op] = &Lexator::_F3Ex;
	state[F3][cmp_op] = &Lexator::_A2o;
	state[F3][lscr] = &Lexator::_F3Ex;
	state[F3][rscr] = &Lexator::_F3Ex;
	state[F3][point] = &Lexator::_F3Ex;
	state[F3][space] = &Lexator::_F3;
	state[F3][Eos] = &Lexator::_F3Ex;
	state[F3][Eof] = &Lexator::_F3Ex;

	state[G1][litter] = &Lexator::_G1;
	state[G1][digit] = &Lexator::_G1;
	state[G1][ar_op] = &Lexator::_G1;
	state[G1][cmp_op] = &Lexator::_G1;
	state[G1][lscr] = &Lexator::_G1;
	state[G1][rscr] = &Lexator::_G1;
	state[G1][point] = &Lexator::_G1;
	state[G1][space] = &Lexator::_G1;
	state[G1][Eos] = &Lexator::_A1;
	state[G1][Eof] = &Lexator::_EXIT1;

	state[H1][litter] = &Lexator::_c2b;
	state[H1][digit] = &Lexator::_D1c;
	state[H1][ar_op] = &Lexator::_A2g;
	state[H1][cmp_op] = &Lexator::_A2p;
	state[H1][lscr] = &Lexator::_A2k;
	state[H1][rscr] = &Lexator::_A3c;
	state[H1][point] = &Lexator::_D6a;
	state[H1][space] = &Lexator::_H1;
	state[H1][Eos] = &Lexator::_A1a;
	state[H1][Eof] = &Lexator::_EXIT2;
}

void Lexator::_A1()
{
	RST = A1;
}

void Lexator::_A1a()
{
	TL.push_back(Lexem(RKL, UTO));
	TO.add_id(RZN);
	RST = A1;
}

void Lexator::_A1b()
{
	_DA1D();

	RST = A1;
}

void Lexator::_A1c()
{
	_DA2D(); _A1a();
	RST = A1;
}

void Lexator::_A1d()
{
	_DA3D(); _A1a();
	RST = A1;
}

void Lexator::_A1e()
{
	_DA1E(); _A1a();
	RST = A1;
}

void Lexator::_A2()
{
	RST = A2;
}

void Lexator::_A2a()
{
	RKL = Ar_Op;
	TL.push_back(Lexem(RKL, RZN));
	RST = A2;
}

void Lexator::_A2b()
{
	//_DA1D();
	if (RKL == Let || RKL == For || RKL == Next) {
		TL.push_back(Lexem(RKL, NTO));	// добавляет let, инд id после let
		TO.add_id(RCH);
	}
	else
		TL.push_back(Lexem(RKL));			// Если ркл не имеет значения

	RST = A2;
}

void Lexator::_A2c()
{
	_DA1D();
	RST = A2;
}

void Lexator::_A2d()
{
	_DA2D(); _A2g();
	RST = A2;
}

void Lexator::_A2e()
{
	_DA3D(); _A2g();
	RST = A2;
}

void Lexator::_A2f()
{
	_DA1E(); _A2g();
	RST = A2;
}

void Lexator::_A2g()
{
	TL.push_back(Lexem(RKL, UTO));
	TO.add_id(RZN);
	_A2a();
}

void Lexator::_A2h()
{
	RKL = lex_type::Lscrub;
	TL.push_back(Lexem(RKL));
	RST = A2;
}

void Lexator::_A2j()
{
	_DA1E();
	RST = A2;
}

void Lexator::_A2k()
{
	RKL = lex_type::Operand;
	TO.add_id(RZN);

	TL.push_back(Lexem(RKL, NTO++));
	RST = A2;
}

void Lexator::_A2l()
{
	_DA1D();_A2k();
	RST = A2;
}

void Lexator::_A2m()
{
	_DA2D(); _A2k();
	RST = A2;
}

void Lexator::_A2n()
{
	_DA3D(); _A2k();
	RST = A2;
}

void Lexator::_A2o()
{
	if (RZN == 0) _A2b();
	else throw OperatorEx("Missing \'=\' after operator");

	RST = A2;
}

void Lexator::_A2p()
{
	int tmp = 0;

	switch (ROT)
	{
	case 2:
		if (RZN == 1 || RZN == 3)
			tmp = (RZN == 1)? 4 : 6;
		break;
	case 3:
		if (RZN == 1)
			tmp = 5;
		break;
	}

	if (!tmp) throw OperatorEx("unknown operation");

	TL.push_back(Lexem(RKL, tmp));

	RST = A2;
}

void Lexator::_A2q()
{
	RKL = End;
	_A2b();
	RST = A2;
}

void Lexator::_A2r()
{
	RKL = If;
	_A2b();
	RST = A2;
}

void Lexator::_A2s()
{
	RKL = Return;
	_A2b();
	RST = A2;
}

void Lexator::_A2t()
{
	RKL = Step;
	_A2b();
	RST = A2;
}

void Lexator::_A2u()
{
	RKL = To;
	_A2b();
	RST = A2;
}

void Lexator::_A3()
{
	RST = A3;
}

void Lexator::_A3a()
{
	UTO += 26 * (RZN + 1);
	TL.push_back(Lexem(RKL, UTO));
}

void Lexator::_A3b()
{
	RKL = lex_type::Rscrub;
	TL.push_back(Lexem(RKL));
	RST = A3;
}

void Lexator::_A3c()
{
	TL.push_back(Lexem(RKL, UTO));
	TO.add_id(RZN);
	//_A3b();
}

void Lexator::_A3d()
{
	_DA1D();
	RST = A3;
}

void Lexator::_A3e()
{
	_DA2D(); _A3c();
	RST = A3;
}

void Lexator::_A3f()
{
	_DA3D(); _A3c();
	RST = A3;
}

void Lexator::_A3g()
{
	_DA1E(); _A3c();
	RST = A3;
}

void Lexator::_B1()
{
	RST = B1;
}

void Lexator::_B1a()
{
	ROB = ROBarr[RZN - 1];
	if (!ROB) throw OperatorEx("This operator incorrct or not exist");

	RST = B1;
}

void Lexator::_B1b()
{
	TL.push_back(Lexem(RKL, UTO));

	//if (ROB == 0) throw OperatorEx("unknown operator");
	RST = B1;

}

void Lexator::_B1c()
{
	_DA3D();
	RST = B1;
}

void Lexator::_B1d()
{
	ROB++;
	RST = B1;
}

void Lexator::_B1e()	// где-то ошибка
{
	_DA1E(); _B1a();

	RST = B1;
}

void Lexator::_C1()
{
	RST = C1;
}

void Lexator::_C1a()
{
	RKL = lex_type::Next;
	RST = C1;
}

void Lexator::_c2()
{
	RST = C2;
}

void Lexator::_c2a()
{
	RKL = lex_type::Operand;
	RST = C2;
}

void Lexator::_c2b()
{
	TL.push_back(Lexem(RKL, ROT));
	_c2a();
}

void Lexator::_c2d()
{
	UTO = RZN;
	RST = C2;
}

void Lexator::_D1()
{
	RST = D1;
}

void Lexator::_D1a()
{
	RKL = lex_type::Operand;
	RCH = RZN;
	RST = D1;
}

void Lexator::_D1b()
{
	RCH = RCH * 10 + (RZN - '0');
	RST = D1;
}

void Lexator::_D1c()
{
	TL.push_back(Lexem(RKL, ROT));
	_D1a();
}

void Lexator::_D2()
{
	RST = D2;
}

void Lexator::_D2a()
{
	++RS;
	_D1b();
	RST = D2;
}

void Lexator::_D2b()
{
	RS = 1;
	RCH = RZN;
	RST = D2;
}

void Lexator::_D2c()
{
	RS = 0;
	RST = D2;
}

void Lexator::_D3()
{
	RST = D3;
}

void Lexator::_D3a()
{
	RS = 0;
	RST = D3;
}

void Lexator::_D4()
{
	RST = D4;
}

void Lexator::_D4a()
{
	switch (RZN)
	{
	case 1: RZ = 1;
		break;
	case 2: RZ = -1;
		break;
	default: throw ConstEx();
	}
	RST = D4;
}

void Lexator::_D5()
{
	RST = D5;
}

void Lexator::_D5a()
{
	RZ = 1;
	RST = D5;
}

void Lexator::_D5b()
{
	RP = RZN;
	RST = D5;
}

void Lexator::_D5c()
{
	RP = RP * 10 + (RZN - '0');
	RST = D5;
}

void Lexator::_D6()
{
	RST = D6;
}

void Lexator::_D6a()
{
	TL.push_back(Lexem(RKL, ROT));
	RST = D6;
}

void Lexator::_E1()
{
	RST = E1;
}

void Lexator::_E1a()
{
	RKL = lex_type::Goto;
	RST = E1;
}

void Lexator::_E1b()
{
	RKL = lex_type::Gosub;
	RST = E1;
}

void Lexator::_E2()
{
	RST = E2;
}

void Lexator::_E2a()
{
	RKL = lex_type::Str_Mark;
	RSTR = RZN;
	RST = E2;
}

void Lexator::_E2b()
{
	RSTR = RZN;
	RST = E2;
}

void Lexator::_E2c()
{
	RSTR = RSTR * 10 + RZN;
	RST = E2;
}

void Lexator::_F1()
{
	RST = F1;
}

void Lexator::_F1a()
{
	RKL = lex_type::Let;
	RST = F1;
}

void Lexator::_F1b()
{
	RKL = For;
	RST = F1;
}

void Lexator::_F2()
{
	RST = F2;
}

void Lexator::_F2a()
{
	UTO = RZN;	// считали let_перем
	RST = F2;
}

void Lexator::_F3()
{
	RST = F3;
}

void Lexator::_F3a()
{
	RZN = (RZN + 1) * 26;
	UTO += RZN;
	RST = F3;
}

void Lexator::_G1()
{
	RST = G1;
}

void Lexator::_G1a()
{
	RKL = Rem;
	TL.push_back(Lexem(RKL));
	RST = G1;
}

void Lexator::_H1()
{
	RST = H1;
}

void Lexator::_H1a()
{
	ROT = RZN;
	RKL = Cmp_Op;
	RST = H1;
}

void Lexator::_H1b()
{
	TL.push_back(Lexem(RKL, UTO));
	TO.add_id(RZN);
	_H1a();
}

void Lexator::_H1c()
{
	_DA1D();
	RST = H1;
}

void Lexator::_H1d()
{
	_DA2D(); _H1b();
	RST = H1;
}

void Lexator::_H1e()
{
	_DA3D(); _H1b();
	RST = H1;
}

void Lexator::_H1f()
{
	_DA1E(); _H1b();
	RST = H1;
}

void Lexator::_M1()
{
	if (TOb[ROB - 1] == RZN)
		switch (ROB)
		{
		case 1: _B1d();
			break;
		case 2: _A2q();
			break;
		case 3: _B1d();
			break;
		case 4: _F1b();
			break;
		case 5:
		case 6: _B1d();
			break;
		case 7: _E1a();
			break;
		case 8:
		case 9: _B1d();
			break;
		case 10: _E1b();
			break;
		case 11: _A2r();
			break;
		case 12: _B1d();
			break;
		case 13: _F1a();
			break;
		case 14:
		case 15: _B1d();
			break;
		case 16: _C1a();
			break;
		case 17:
		case 18:
		case 19:
		case 20: _B1d();
			break;
		case 21: _A2s();
			break;
		case 22: _G1a();
			break;
		case 23:
		case 24: _B1d();
			break;
		case 25: _A2t();
			break;
		case 26: _A2u();
			break;
		default: throw ExceptM1();
		}
	else throw OperatorEx("unknown operator");
}

void Lexator::_M2()
{
	if (RZN == 5) _D3a();
	else { _DA1D(); _B1b2(); }
}

void Lexator::_B1b2()
{
	TL.push_back(Lexem(RKL, NTO)); ++NTO;
	
	TO.add_id(RCH);

	ROB = ROBarr[RZN - 1];
	if (!ROB) throw OperatorEx("unknown operator");


}
void Lexator::_M3()
{
	if (RZN == 5) _D3();
	else { _DA2D(); _B1b2(); }
}

void Lexator::_EXIT1()
{
	RKL = lex_type::End;

	TL.push_back(Lexem(RKL));
	
	RST = EXIT;
}

void Lexator::_EXIT2()
{
	TL.push_back(Lexem(RKL, ROT));
}

void Lexator::_EXIT3()
{
	_DA1D();
}

void Lexator::_EXIT4()
{
	_DA2D(); _EXIT2();
}

void Lexator::_EXIT5()
{
	_DA3D(); _EXIT2();
}

void Lexator::_EXIT6()
{
	_DA1E(); _EXIT2();
}

void Lexator::_DA1D()
{
	RP = 0;

	TO.add_const(RCH);	NTO++;
	TL.push_back({ Operand, RCH });
	
}

void Lexator::_DA2D()
{
	RP = pow(10.0, -RS);
	RCH *= RP;
}

void Lexator::_DA3D()
{
	if (RZ == -1) RP = -RP;

	RP -= RS;
	RP = pow(10.0, RP);

	RCH *= RP;
}

void Lexator::_DA1E()
{
	size_t q = TS.add({ RSTR, TL.size() + 1 });

	TL.push_back(Lexem(RKL, q));
}

void Lexator::_A1Ex() { throw Except1(); }
void Lexator::_A2Ex() { throw ExceptA2(); }
void Lexator::_A3Ex() { throw ExceptA3(); }
void Lexator::_B1Ex() { throw OperatorEx("Unknown operator"); }
void Lexator::_C1Ex() { throw Except2(); }
void Lexator::_C2Ex() { throw Except3(); }
void Lexator::_D1Ex() { throw ExceptD1(); }
void Lexator::_D2Ex() { throw Except4(); }
void Lexator::_D36Ex(){ throw ConstEx(); }
void Lexator::_E1Ex() { throw  Except5(); }
void Lexator::_E2Ex() { throw  Except6(); }
void Lexator::_F1Ex() { throw  Except7(); }
void Lexator::_F2Ex() { throw  Except8(); }
void Lexator::_F3Ex() { throw  Except9(); }
void Lexator::_H1Ex() { throw  ExceptH1(); }

//void Lexator::_DA1ECircle()
//{
//
//}
void Operands::add_id(string& id_)
{
	size_t ind = calculate(id_);
	if (ind != -1)
		identif[ind] = true;
}

bool Operands::find(string& str_) const
{
	char c = toupper(str_.front());
	size_t ind = calculate(str_);
	if (ind != -1)
		return identif[ind];
	
		double d = stod(str_);
		for (double x : consts)
			if (x == d) return true;
		return false;
	
}
size_t Operands::calculate(string& id_) const
{
	char c = toupper(id_.front());
	size_t ind = -1;
	if (c >= 'A' && c <= 'Z')
	{
		size_t i;
		i = toupper(c) - 'A';
		if (id_.size() == 1)
			ind = i;
		else if (id_.size() == 2)
				ind = (i * 26) * (id_[1] - '0' + 1);
	}
	return ind;
}

