#pragma once
#include"stdc++.h"
using namespace std;
void error()
{
	throw invalid_argument("Invalid");
}
void error(string s)
{
	throw invalid_argument(s);
}