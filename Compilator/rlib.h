#pragma once
#include <string>

struct syntax_except {};	// любая синтаксич. ошибка


const std::string op_single = " .()+-*/%=&|><"; 

const size_t g_dualOp = 3;
const std::string op_dual[g_dualOp] = {	"<>", "<=", ">=" };

bool digit(const char&);
bool litter(const char&);
bool dig_or_lit(const char&);

bool isNatural(const std::string&);
bool isVar(const std::string&);

//size_t get_priority(const std::string& op_);

std::string pop_front(std::string&);
