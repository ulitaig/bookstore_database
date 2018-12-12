#pragma once
#include"stdc++.h"
#include"error.h"
#include"user.h"
#include"node.h"
#include"finance.h"
using namespace std;
namespace search_index
{
	const string idx[] = { "user","ISBN","name","author","keyword" };
	int bn[10];
	const int bs = 50000;
	fstream bkf, usf;
	int bkn, usn;
	vector<fstream> fs[10];
	vector<int> nxt[10], bc[10];
	vector<node> start[10];
	inline string id(int i)
	{
		char ch[10];
		memset(ch, 0, sizeof(ch));
		int l = 0, z=10;
		while (i >= z) z *= 10;
		z /= 10;
		while(z>=1)
		{
			ch[l] ='0'+ i / z;
			i %= 10;
			z /= 10;
			l++;
		}
		string ss;
		ss.resize(l);
		ss = ch;
		return ss;
	}
	void insert(node o, int d)
	{
		int k;
		for (k = 1; nxt[d][k] != 0; k = nxt[d][k])
		{
			if (o < start[d][nxt[d][k]]) break;
		}
		fs[d][k].seekg(0,ios::end);
		o.write(fs[d][k]);

		fs[d][k].seekp(0);
		o.read(fs[d][k]);


		bc[d][k]++;
		if (bc[d][k] > bs)
		{
			/*if (d == 3&&bn[d]==30)
				puts("oooooooops");*/
			node *p = new node[bc[d][k] + 5];
			fs[d][k].seekg(0);
			for (int i = 0; i < bc[d][k]; i++)
			{
				p[i].read(fs[d][k]);
			}
			start[d].push_back(p[bs / 2]);
			nxt[d].push_back(nxt[d][k]);
			nxt[d][k] = bn[d];

			ofstream ofs(idx[d] + id(bn[d]), ios::binary);
			ofs.close();
			fs[d].push_back(fstream(idx[d] + id(bn[d]), ios::in | ios::out | ios::binary));
			start[d][bn[d]].write(fs[d][bn[d]]);

			fs[d][k].close();
			ofs.open(idx[d] + id(k), ios::binary);
			ofs.close();
			fs[d][k].open(idx[d] + id(k), ios::in | ios::out | ios::binary);
			fs[d][k].seekg(0);

			int nn = bc[d][k];
			bc[d][k] = 0;
			bc[d].push_back(1);
			for (int i = 0; i < nn; i++)
			{
				if (i == bs / 2 || p[i].is_del()) continue;
				if (p[i] < start[d][bn[d]])
				{
					p[i].write(fs[d][k]);
					bc[d][k]++;
				}
				else
				{
					p[i].write(fs[d][bn[d]]);
					bc[d][bn[d]]++;
				}
			}
			bn[d]++;
			delete p;
		}
	}
	vector<int> search(node o, int d)
	{
		vector<int> ans;
		int k;
		for (k = 1; nxt[d][k] != 0; k = nxt[d][k])
		{
			if (o < start[d][nxt[d][k]]) break;
		}
		fs[d][k].seekp(0);
		node a;
		for (int i = 0; i < bc[d][k]; i++)
		{
			a.read(fs[d][k]);
			if (o == a && !a.is_del())
			{
				ans.push_back(a.id);
			}
		}
		return ans;
	}
	void del_idx(node o, int d)
	{
		int k;
		for (k = 1; nxt[d][k] != 0; k = nxt[d][k])
		{
			if (o < start[d][nxt[d][k]]) break;
		}
		fs[d][k].seekp(0);
		node a;
		for (int i = 0; i < bc[d][k]; i++)
		{
			fs[d][k].seekg(i * sizeof(node));
			a.read(fs[d][k]);
			if (o == a)
			{
				a.del_node();
				fs[d][k].seekg(i * sizeof(node));
				a.write(fs[d][k]);
			}
		}
	}
	user get_user(int id)
	{
		user o;
		usf.seekp(id * sizeof(user));
		o.read(usf);
		return o;
	}
	void mdf_user(int id, const user &o)
	{
		usf.seekp(id * sizeof(user));
		o.write(usf);
	}
	void add_user(user o)
	{
		usf.seekp(usn * sizeof(user));
		o.write(usf);
		node no(o.id, 30, usn);
		usn++;
		insert(no, 0);
	}
	void init()
	{
		ifstream ifs("datasize", ios::binary);
		if (!ifs)
		{
			ofstream ofs("users", ios::binary);
			user root("root", "sjtu", "root", 7);
			root.write(ofs);
			ofs.close();
			//usf.open("users", ios::in | ios::out | ios::binary);
			ofs.open("books", ios::binary);
			ofs.close();
			//bkf.open("books", ios::in | ios::out | ios::binary);
			for (int i = 0; i < 5; i++)
			{
				//ofs.open("fuck");
				//ofs.close();
				//cout << idx[i] + id(0) << endl;
				ofs.open(idx[i] + id(0), ios::binary);
				//if (!ofs) puts("##fuck");
				Write(2, ofs);
				Write(0, ofs);
				Write(1, ofs);
				ofs.close();
				//fs[i].push_back(fstream(idx[i] + id(0), ios::in | ios::out | ios::binary));
				ofs.open(idx[i] + id(1), ios::binary);
				node o;
				o.write(ofs);
				ofs.close();
				//fs[i].push_back(fstream(idx[i] + id(1), ios::in | ios::out | ios::binary));
				//bn[i] = 2;
			}
			ofs.open("user0", ios::binary);
			Write(2, ofs);
			Write(0, ofs);
			Write(1, ofs);
			ofs.close();
			ofs.open("user1", ios::binary);
			node o(root.id, 30, 0);
			o.write(ofs);
			ofs.close();
			usn = 1; bkn = 0;
			ofs.open("datasize", ios::binary);
			Write(usn, ofs);
			Write(bkn, ofs);
			double db = 0.0;
			Write(db, ofs);
			Write(db, ofs);
			Write(0, ofs);
			ofs.close();
			//return;
		}
		else
		{
			Read(usn, ifs);
			Read(bkn, ifs);
			Read(finance::in, ifs);
			Read(finance::out, ifs);
			Read(finance::cnt, ifs);
			ifs.close();
		}
		usf.open("users", ios::in | ios::out | ios::binary);
		bkf.open("books", ios::in | ios::out | ios::binary);
		for (int i = 0; i < 5; i++)
		{
			fs[i].push_back(fstream(idx[i] + id(0), ios::in | ios::out | ios::binary));
			Read(bn[i], fs[i][0]);
			start[i].push_back(node());
			nxt[i].push_back(0);
			bc[i].push_back(0);
			for (int j = 1; j < bn[i]; j++)
			{
				fs[i].push_back(fstream(idx[i] + id(j), ios::in | ios::out | ios::binary));
				//if (!fs[i][j]) puts("fuck");
				//cout << idx[i] + id(j) << endl;
				node o;
				o.read(fs[i][j]);
				start[i].push_back(o);
				int nx, bbc;
				Read(nx, fs[i][0]);
				Read(bbc, fs[i][0]);
				nxt[i].push_back(nx);
				bc[i].push_back(bbc);
			}
		}
		finance::init();
	}
	void save0()
	{
		for (int i = 0; i < 5; i++)
		{
			fs[i][0].seekg(0);
			Write(bn[i], fs[i][0]);
			for (int j = 1; j < bn[i]; j++)
			{
				Write(nxt[i][j], fs[i][0]);
				Write(bc[i][j], fs[i][0]);
			}
		}
		ofstream ofs("datasize", ios::binary);
		Write(usn, ofs);
		Write(bkn, ofs);
		Write(finance::in, ofs);
		Write(finance::out, ofs);
		Write(finance::cnt, ofs);
		ofs.close();
	}
}

