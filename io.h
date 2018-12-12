#pragma once
#include"stdc++.h"
#include"error.h"
using namespace std;
template <class T>
bool Read(T &a,ifstream &is)
{
	if (is.eof()) error();
	is.read(reinterpret_cast<char *>(&a), sizeof(a));
	return true;
}
template <class T>
void Write(const T &a, ofstream &os)
{
	os.write(reinterpret_cast<const char *>(&a), sizeof(a));
}
template <class T>
bool Read(T &a, fstream &is)
{
	if (is.eof()) error();
	is.read(reinterpret_cast<char *>(&a), sizeof(a));
	return true;
}
template <class T>
void Write(const T &a, fstream &os)
{
	os.write(reinterpret_cast<const char *>(&a), sizeof(a));
}