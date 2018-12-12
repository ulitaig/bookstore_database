#pragma once
#include"stdc++.h"
#include"io.h"
#include"error.h"
using namespace std;
namespace finance
{
	double in, out;
	int cnt;
	fstream fs;
	void init()
	{
		ifstream ifs("finance", ios::binary);
		if (!ifs)
		{
			ofstream ofs("finance", ios::binary);
			ofs.close();
		}
		else ifs.close();
		fs.open("finance", ios::in | ios::out | ios::binary);
	}
	void add(double d)
	{
		fs.seekg(0, ios::end);
		Write(d, fs);
		cnt++;
		if(d<0.0) out -= d;
		else in += d;
	}
	void putout(int t)
	{
		if (t > cnt) t = cnt;
		double d,d1=0.0,d2=0.0;
		for (int i = 1; i <= t; i++)
		{
			fs.seekg((cnt-i)*sizeof(double));
			Read(d, fs);
			if (d < 0.0) d2 -= d;
			else d1 += d;
		}
		printf("+ %.2lf - %.2lf\n", d1, d2);
	}
	void putout()
	{
		printf("+ %.2lf - %.2lf\n", in, out);
	}
};