#pragma once
#include"stdc++.h"
#include"error.h"
#include"search.h"
#include"finance.h"
#include"node.h"
using namespace std;
using namespace index;
class book
{
private:
	char ISBN[20];
	char name[40];
	char author[40];
	char keyword[40];
	int quantity;
	double price;
public:
	book()
	{
		clear();
	}
	book(const int &i)
	{
		clear();
		this->get_book(i);
	}
	bool operator < (const book &B) const 
	{
		string a(ISBN), b(B.ISBN);
		return a < b;
	}
	void clear()
	{
		memset(ISBN, 0, sizeof(ISBN));
		memset(name, 0, sizeof(name));
		memset(author, 0, sizeof(author));
		memset(keyword, 0, sizeof(keyword));
		price = 0.0; quantity = 0;
	}
	int mdy_ISBN(string s,int id=-1)
	{
		if (id == -1)
		{
			id = bkn;
			bkn++;
		}
		if (ISBN[0] != 0)
		{
			node o(ISBN, 20, id);
			del_idx(o, 1);
		}
		memset(ISBN, 0, sizeof(ISBN));
		for (int i = 0; i < (int)s.length(); i++) ISBN[i] = s[i];
		node o(s, id);
		insert(o, 1);
		bkf.seekp(id * sizeof(book));
		this->write(bkf);
		return id;
	}
	void mdy_name(string s, int id)
	{
		if (name[0] != 0)
		{
			node o(name, 40, id);
			del_idx(o, 2);
		}
		memset(name, 0, sizeof(name));
		for (int i = 0; i < (int)s.length(); i++) name[i] = s[i];
		node o(s, id);
		insert(o, 2);
		bkf.seekp(id * sizeof(book));
		this->write(bkf);
	}
	void mdy_author(string s, int id)
	{
		if (author[0] != 0)
		{
			node o(author, 40, id);
			del_idx(o, 3);
		}
		memset(author, 0, sizeof(author));
		for (int i = 0; i < (int)s.length(); i++) author[i] = s[i];
		node o(s, id);
		insert(o, 3);
		bkf.seekp(id * sizeof(book));
		this->write(bkf);
	}
	void mdy_keyword(string s, int id)
	{
		if (keyword[0] != 0)
		{
			int st = 0;
			for (int i = 0; i < 40; i++)
			{
				if (keyword[i] == '|')
				{
					string s(keyword+st, keyword+i);
					node o(s, id);
					del_idx(o, 4);
					st = i + 1;
				}
			}
			string s(keyword + st);
			node o(s, id);
			del_idx(o, 4);
		}
		memset(keyword, 0, sizeof(keyword));
		int st = 0;
		for (int i = 0; i < (int)s.length(); i++)
		{
			keyword[i] = s[i];
			if (s[i] == '|')
			{
				node o(s.substr(st, i - st), id);
				insert(o, 4);
				st = i + 1;
			}
		}
		node o(s.substr(st, s.length() - st), id);
		insert(o, 4);
		bkf.seekp(id * sizeof(book));
		this->write(bkf);
	}
	void mdy_price(const double &pr,int id)
	{
		price = pr;
		bkf.seekp(id * sizeof(book));
		this->write(bkf);
	}
	void mdy_quantity(const int &z, int id)
	{
		quantity += z;
		bkf.seekp(id * sizeof(book));
		this->write(bkf);
	}
	void write(ofstream &os)
	{
		os.write(ISBN, sizeof(ISBN));
		os.write(name, sizeof(name));
		os.write(author, sizeof(author));
		os.write(keyword, sizeof(keyword));
		Write(price, os);
		Write(quantity, os);
	}
	void read(ifstream &is)
	{
		if (is.eof()) error();
		is.read(ISBN, sizeof(ISBN));
		if (is.eof()) error();
		is.read(name, sizeof(name));
		if (is.eof()) error();
		is.read(author, sizeof(author));
		if (is.eof()) error();
		is.read(keyword, sizeof(keyword));
		if (is.eof()) error();
		Read(price, is);
		if (is.eof()) error();
		Read(quantity, is);
	}
	void write(fstream &os)
	{
		os.write(ISBN, sizeof(ISBN));
		os.write(name, sizeof(name));
		os.write(author, sizeof(author));
		os.write(keyword, sizeof(keyword));
		Write(price, os);
		Write(quantity, os);
	}
	void read(fstream &is)
	{
		if (is.eof()) error();
		is.read(ISBN, sizeof(ISBN));
		if (is.eof()) error();
		is.read(name, sizeof(name));
		if (is.eof()) error();
		is.read(author, sizeof(author));
		if (is.eof()) error();
		is.read(keyword, sizeof(keyword));
		if (is.eof()) error();
		Read(price, is);
		if (is.eof()) error();
		Read(quantity, is);
	}
	void get_book(const int &id)
	{
		bkf.seekp(id * sizeof(book));
		this->read(bkf);
	}
	bool check(int n) { return quantity >= n; }
	const double get_price() { return price; }
	void out() const
	{
		cout << fixed << setprecision(2) << ISBN << "\t" << name << "\t" << author << "\t" << keyword << "\t" << price << "\t" << quantity << "本" << endl;
	}
};