#pragma once
#include"stdc++.h"
#include"io.h"
#include"error.h"
using namespace std;
class node
{
private:
	static const int N = 40;
	char s[N];
public:
	int id;
	node(int i = 0) :id(i) { memset(s, 0, sizeof(s)); };
	node(string a,int i=0):id(i)
	{

		memset(s, 0, sizeof(s));
		for (int i = 0; i < (int)a.length(); i++) s[i] = a[i];
	}
	node(const char *a,const int &n,const int &i ) :id(i)
	{
		memset(s, 0, sizeof(s));
		for (int i = 0; i < n; i++) s[i] = a[i];
	}
	void del_node() { id = -1; }
	bool is_del() { return id==-1; }
	void write(fstream &os)
	{
		os.write(s, sizeof(s));
		Write(id, os);
	}
	void read(fstream &is)
	{
		if (is.eof()) error();
		is.read(s, sizeof(s));
		Read(id, is);
	}
	void write(ofstream &os)
	{
		os.write(s, sizeof(s));
		Write(id, os);
	}
	void read(ifstream &is)
	{
		if (is.eof()) error();
		is.read(s, sizeof(s));
		Read(id, is);
	}
	bool operator <(const node &b) const
	{
		for (int i = 0; i < N; i++)
			if (s[i] < b.s[i]) return true;
			else if (s[i] > b.s[i]) return false;
		return false;
	}
	bool operator ==(const node &b) const
	{
		for (int i = 0; i < N; i++)
			if (s[i] != b.s[i]) return false;
		return true;
	}
};
