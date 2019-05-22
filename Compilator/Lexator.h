#pragma once
#include <string>
#include <list>
#include <algorithm>
#include <ostream>
const size_t g_table = 100;
const size_t g_id = 258;

size_t rconvert(const std::string*, size_t, const std::string&);
/* Доделать соответствие енама и строк*/

const std::string c_Lex[] =
{	
	"Mark",		"Operand",
	"Ar_Op",	"Cmp_Op",
	"NEXT",		"LET",
	"FOR",		
	"GOTO",		"GOSUB",
	"(",		")",
	"IF",		"RETURN",
	"END",		"TO",
	"STEP",		"REM",
	"Error"
};
enum lex_type
{
	Str_Mark,	Operand,
	Ar_Op,		Cmp_Op,
	Next,		Let,
	For,
	Goto,		Gosub,
	Lscrub,		Rscrub,
	If, Return, End,
	To, Step,	Rem,
	Err
};

const std::string c_ArOp[] =
					{ "+", "-", "*", "/", "^" };
enum class ArOp		{ add, dif, multi, div, pwr };

const std::string c_CmpOp[] =
					{	"=", "<", ">", "<=", ">=", "<>" };
enum class CmpOp	{ equal, les, more, leq, moq, unequal };

enum Token
{
	litter, digit, ar_op, cmp_op,
	lscr, rscr,
	point, space, Eos, Eof
};
enum States
{
	A1, A2, A3,
	B1,
	C1, C2,
	D1, D2, D3, D4, D5, D6,
	E1, E2,
	F1, F2, F3,
	G1,
	H1,
	EXIT
};
struct Lexem
{
	lex_type type;
	size_t	value;

	Lexem(lex_type t = Err, size_t v = -1)
		: type(t), value(v)
	{}

	// дописать
	friend std::ostream& operator <<(std::ostream& out, const Lexem& lex)
	{
		
		out << '(' << c_Lex[lex.type] << ", ";
		if (lex.value != -1)
			out << lex.value;
		else
			out << "--";

		out << ')';
		return out;
	}
};
class StrTable
{
	struct StrField
	{
		size_t mark;
		size_t num_lex;
		
		StrField(size_t mark = -1, size_t num_lex = -1,
			size_t next = -1) : mark(mark), num_lex(num_lex)
		{}
		bool operator == (const StrField& lex_)const
		{
			return mark == lex_.mark;
		}

		friend std::ostream& operator<<(std::ostream& os, const StrField& obj) {
			return os << obj.mark <<'\t'<< obj.num_lex;
		}
	};
public:
	StrTable() = default;
	size_t add(StrField field_)
	{
		size_t ind = field_.mark % 100;
		//StrField entry(mark_);

		auto frst = field[ind].begin();
		auto lst = field[ind].end();
		auto t = std::find(frst, lst, field_);
		
		//if (t != lst)
			field[ind].push_front(field_);
		return ind;
	}
	
	friend std::ostream& operator << (std::ostream& os, const StrTable& s) {
		for (size_t i = 1; i < 101; i++)
		{
			os << '\t' << i << ":\n";
			for (StrField x : s.field[i])
				os << "\t\t" << x << std::endl;
		}
		return os;
	}
private:
	std::list<StrField> field[101];
};
class Operands
{
public:
	Operands(){
		for (size_t i = 0; i < g_id; i++)
			identif[i] = 0;
	}
	void add_const(const double& key_){
		consts.push_back(key_);
	}

	void add_id(const size_t& id_){
		identif[id_] = true;
	}
	void add_id(std::string& id_);

	bool find(std::string&) const;								// b1 == (1 + 26*(1 + 1)) == 
	friend std::ostream& operator<<(std::ostream& os, const Operands& obj) {
		os << "Identificators\n";
		for (size_t i = 0; i < 26; i++)
			if (obj.identif[i])
				os << '\t' << char('A' + i) << std::endl;
		
		char a = 'A';
		char d = '0';
		for (size_t i = 26; i< 258; i++, d++)
		{
			if (obj.identif[i])
				os << '\t' << (char)a << d << std::endl;

			if (d == '9')
			{
				d = '0';
				a++;
			}
		}

		os << "CONSTS\n";
		for (double x : obj.consts)
			os << '\t' << x << std::endl;
		return os;
	}
	size_t size() const;
	~Operands() = default;

private:
	size_t calculate(std::string&) const;
private:
	bool identif[g_id];
	std::list<double> consts;
};

class Lexator
{
public:
	
	void typedef (Lexator::*pFun)();
	Lexator();
	void start(const char*, const char*, const char*);

	void translit(char c);
	~Lexator() = default;

private:
	
	void init();

	void _A1();
	void _A1a();
	void _A1b();
	void _A1c();
	void _A1d();
	void _A1e();

	// 21
	void _A2();
	void _A2a();
	void _A2b();
	void _A2c();
	void _A2d();
	void _A2e();
	void _A2f();
	void _A2g();
	void _A2h();
	void _A2j();
	void _A2k();
	void _A2l();
	void _A2m();
	void _A2n();
	void _A2o();
	void _A2p();
	void _A2q();
	void _A2r();
	void _A2s();
	void _A2t();
	void _A2u();

	void _A3();
	void _A3a();
	void _A3b();
	void _A3c();
	void _A3d();
	void _A3e();
	void _A3f();
	void _A3g();

	void _B1();
	void _B1a();
	void _B1b();
	void _B1c();
	void _B1d();
	void _B1e();

	void _C1();
	void _C1a();

	void _c2();
	void _c2a();
	void _c2b();
	void _c2d();

	void _D1();
	void _D1a();
	void _D1b();
	void _D1c();

	void _D2();
	void _D2a();
	void _D2b();
	void _D2c();

	void _D3();
	void _D3a();

	void _D4();
	void _D4a();

	void _D5();
	void _D5a();
	void _D5b();
	void _D5c();

	void _D6();
	void _D6a();

	void _E1();
	void _E1a();
	void _E1b();

	void _E2();
	void _E2a();
	void _E2b();
	void _E2c();

	void _F1();
	void _F1a();
	void _F1b();

	void _F2();
	void _F2a();

	void _F3();
	void _F3a();

	void _G1();
	void _G1a();

	void _H1();
	void _H1a();
	void _H1b();
	void _H1c();
	void _H1d();
	void _H1e();
	void _H1f();

	void _M1();
	void _M2();
	void _B1b2();
	void _M3();

	void _EXIT1();
	void _EXIT2();
	void _EXIT3();
	void _EXIT4();
	void _EXIT5();
	void _EXIT6();

	void _DA1D();
	void _DA2D();
	void _DA3D();

	void _DA1E();
	//void _DA1ECircle();

	void _A1Ex();
	void _A2Ex();
	void _A3Ex();

	void _B1Ex();

	void _C1Ex();
	void _C2Ex();

	void _D1Ex();
	void _D2Ex();
	void _D36Ex(); // 3 - 6

	void _E1Ex();
	void _E2Ex();

	void _F1Ex();
	void _F2Ex();
	void _F3Ex();

	void _H1Ex();
private:
	std::string str;

	int RZ, RS, RP;	// регистр знака
	size_t RCH, RSTR;
	size_t ROB, RZN, ROT;
	size_t UTO, NTO, UTS, NTS,  UTL ;

	States RST;
	lex_type RKL;
	Token RK;

	pFun state[19][10];
	
	size_t ROBarr[26];
	size_t TOb[26];

	std::list<Lexem> TL;
	StrTable TS;
	Operands TO;
};

