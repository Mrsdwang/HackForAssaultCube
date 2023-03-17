#pragma once
#include "framework.h"

class InternalEspInfo {
private:
	static const int MAX_PLAYERS = 32;
public:

	float x_val[MAX_PLAYERS+1] = { 0 };
	float y_val[MAX_PLAYERS+1] = { 0 };
	std::string print_text[MAX_PLAYERS+1] = { "" };
};