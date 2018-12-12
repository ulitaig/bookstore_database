#pragma once
#include"stdc++.h"
#include"io.h"
#include"error.h"
using namespace std;
class user
{
private:
	char pwd[30];
public:
	char id[30];
	int permission;
	char name[20];
	user()
	{
		memset(id, 0, sizeof(id));
		memset(pwd, 0, sizeof(pwd));
		memset(name, 0, sizeof(name));
		permission = 1;
	}
	user(string a,string b,string c,int su)
	{
		memset(id, 0, sizeof(id));
		memset(pwd, 0, sizeof(pwd));
		memset(name, 0, sizeof(name));
		permission = su;
		for (int i = 0; i < (int)a.length(); i++)
			id[i] = a[i];
		for (int i = 0; i < (int)b.length(); i++)
			pwd[i] = b[i];
		for (int i = 0; i < (int)c.length(); i++)
			name[i] = c[i];
	}
	string get_pwd() { return string(pwd); }
	void set_pwd(string s)
	{
		memset(pwd, 0, sizeof(pwd));
		for (int i = 0; i < (int)s.length(); i++)
			pwd[i] = s[i];
	}
	void write(ofstream &os) const
	{
		os.write(id, sizeof(id));
		os.write(pwd, sizeof(pwd));
		os.write(name, sizeof(name));
		Write(permission, os);
	}
	void read(ifstream &is)
	{
		if (is.eof()) error();
		is.read(id, sizeof(id));
		if (is.eof()) error();
		is.read(pwd, sizeof(pwd));
		if (is.eof()) error();
		is.read(name, sizeof(name));
		if (is.eof()) error();
		Read(permission, is);
	}
	void write(fstream &os) const
	{
		os.write(id, sizeof(id));
		os.write(pwd, sizeof(pwd));
		os.write(name, sizeof(name));
		Write(permission, os);
	}
	void read(fstream &is)
	{
		if (is.eof()) error();
		is.read(id, sizeof(id));
		if (is.eof()) error();
		is.read(pwd, sizeof(pwd));
		if (is.eof()) error();
		is.read(name, sizeof(name));
		if (is.eof()) error();
		Read(permission, is);
	}
};