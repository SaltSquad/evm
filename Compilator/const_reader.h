#pragma once

#include <string>

class const_reader
{
public:
	const_reader();

	void setWord(std::string);
	bool Lets_Go(double& result_);

	~const_reader();

private:

	void A0(const char& ch);
	void A1(const char& ch);
	void A2(const char& ch);
	void A3(const char& ch);
	void A4(const char& ch);
	void A5(const char& ch);
	void A6(const char& ch);

private:

	std::string str;

	void typedef (const_reader::*fs)(const char& ch);
	fs ptr;
	int r_CH, r_S, r_P;
	bool negtv;

};

