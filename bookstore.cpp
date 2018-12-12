#include"stdc++.h"
#include"error.h"
#include"book.h"
#include"user.h"
#include"search.h"
#include"finance.h"
using namespace std;
using namespace search_index;
char line[800];
int permission;
string user_id;
book select_book;
int select_id = -1;
template <class T>
void DO(T &ifs);
int main()
{
	/*cin.getline(line, 800,'#');
	char asd[10];
	memset(asd, 0, sizeof(asd));
	cout << asd<<endl;
	string qwe(line);
	qwe=qwe.substr(3, 2);
	cout << qwe <<"@"<<qwe.length()<< endl;
	while(1) getchar();
	return 0;*/
	//cout << sizeof(node);

	init();

	/*node o("1" ,3);
	node a;
	fs[0][1].seekg(0);
	for (int i = 0; i < bc[0][1]; i++)
	{
		fs[0][1].seekg(i * sizeof(node), 0);
		a.read(fs[0][1]);
		if (o == a)
		{
			a.del_node();
			fs[0][1].seekg(i * sizeof(node),0);
			a.write(fs[0][1]);
			fs[0][1].seekg(i * sizeof(node), 0);
			a.read(fs[0][1]);
		}
	}
	return 0;*/

	ifstream ifs("command.txt");
	if (!ifs)
	{
		user_id = "unregister";
		permission = 0;
		DO(cin);
	}
	else
	{
		user_id = "root";
		permission = 7;
		DO(ifs);
	}
	//getchar(); getchar();
	return 0;
}
template <class T>
void DO(T &ifs)
{
	while (!ifs.eof())
	{
		string s[10];
		ifs.getline(line, 800);
		int l = strlen(line);
		if (l > 500) { puts("WTF!"); exit(520); }
		stringstream ss(line);
		ss >> s[0];
		if (s[0] == "load")
		{
			ss >> s[1];
			ifstream is(s[1]);
			if (!is) { puts("Invalid"); continue; }
			ss >> s[2];
			if (!s[2].empty()) { puts("Invalid"); continue; }
			DO(is);
			is.close();
		}
		else if (s[0] == "exit")
		{
			ss >> s[1];
			if (!s[1].empty()) { puts("Invalid"); continue; }
			save0();
			return;
		}
		else if (s[0] == "su")
		{
			ss >> s[1];
			ss >> s[2];
			ss >> s[3];
			if (s[1].empty() || !s[3].empty()) { puts("Invalid"); continue; }
			vector<int> id = search(node(s[1]), 0);
			if (!id.size()) { puts("Invalid"); continue; }
			user us = get_user(id[0]);
			if (us.permission >= permission)
				if (us.get_pwd() != s[2]) { puts("Invalid"); continue; }
			permission = us.permission;
			user_id = us.name;
		}
		else if (s[0] == "logout")
		{
			ss >> s[1];
			if (!s[1].empty()) { puts("Invalid"); continue; }
			if (permission < 1) { puts("Invalid"); continue; }
			user_id = "unregister";
			permission = 0;
		}
		else if (s[0] == "useradd")
		{
			ss >> s[1];
			ss >> s[2];
			int ps;
			ss >> ps;
			ss >> s[3];
			ss >> s[4];
			if (s[1].empty() || s[2].empty() || s[3].empty() || !s[4].empty() || (ps != 1 && ps != 3 && ps != 7))
			{
				puts("Invalid"); continue;
			}
			if (ps >= permission) { puts("Invalid"); continue; }
			vector<int> id = search(node(s[1]), 0);
			if (id.size()) { puts("Invalid"); continue; }
			user us(s[1], s[2], s[3], ps);
			add_user(us);
		}
		else if (s[0] == "register")
		{
			ss >> s[1];
			ss >> s[2];
			ss >> s[3];
			ss >> s[4];
			if (s[1].empty() || s[2].empty() || s[3].empty() || !s[4].empty())
			{
				puts("Invalid"); continue;
			}
			vector<int> id = search(node(s[1]), 0);
			if (id.size()) { puts("Invalid"); continue; }
			user us(s[1], s[2], s[3], 1);
			add_user(us);
		}
		else if (s[0] == "delete")
		{
			if (permission < 7) { puts("Invalid"); continue; }
			ss >> s[1];
			ss >> s[2];
			if (s[1].empty() || !s[2].empty())
			{
				puts("Invalid"); continue;
			}
			vector<int> id = search(node(s[1]), 0);
			if (!id.size()) { puts("Invalid"); continue; }
			del_idx(node(s[1]), 0);
		}
		else if (s[0] == "passwd")
		{
			if (permission < 1) { puts("Invalid"); continue; }
			ss >> s[1];
			ss >> s[2];
			ss >> s[3];

			if (permission == 7)
			{
				if (s[1].empty() || s[2].empty() || !s[3].empty())
				{
					puts("Invalid"); continue;
				}
				vector<int> id = search(node(s[1]), 0);
				if (!id.size()) { puts("Invalid"); continue; }
				user us = get_user(id[0]);
				us.set_pwd(s[2]);
				mdf_user(id[0], us);
			}
			else
			{
				ss >> s[4];
				if (s[1].empty() || s[2].empty() || s[3].empty() || !s[4].empty())
				{
					puts("Invalid"); continue;
				}
				vector<int> id = search(node(s[1]), 0);
				if (!id.size()) { puts("Invalid"); continue; }
				user us = get_user(id[0]);
				if (us.get_pwd() != s[2]) { puts("Invalid"); continue; }
				us.set_pwd(s[3]);
				mdf_user(id[0], us);
			}
		}
		else if (s[0] == "select")
		{
			if (permission < 3) { puts("Invalid"); continue; }
			ss >> s[1];
			ss >> s[2];
			if (s[1].empty() || !s[2].empty()) { puts("Invalid"); continue; }
			vector<int> id = search(node(s[1]), 1);
			if (!id.size())
			{
				select_book.clear();
				select_id = select_book.mdy_ISBN(s[1]);
			}
			else
			{
				select_book.get_book(id[0]);
				select_id = id[0];
			}
			/*if (s[1] == "123456789333")
				puts("fuck");*/
		}
		else if (s[0] == "modify")
		{
			if (permission < 3) { puts("Invalid"); continue; }
			if (select_id < 0) { puts("Invalid"); continue; }
			bool succ = true;
			double pr = -1;
			while (!ss.eof())
			{
				ss.getline(line, 800, '=');
				int st = 0;
				while (line[st] == ' ') st++;
				string prmt(line + st);
				if (prmt.empty()) break;
				if (prmt == "-ISBN")
				{
					if (!s[1].empty()) { succ = false; break; }
					ss >> s[1];
					if (s[1].empty()) { succ = false; break; }
					vector<int> id = search(node(s[1]), 1);
					if (id.size()) { succ = false; break; }
				}
				else if (prmt == "-name")
				{
					if (!s[2].empty()) { succ = false; break; }
					ss.getline(line, 800, '"');
					ss.getline(line, 800, '"');
					s[2] = line;
					if (s[2].empty()) { succ = false; break; }
				}
				else if (prmt == "-author")
				{
					if (!s[3].empty()) { succ = false; break; }
					ss.getline(line, 800, '"');
					ss.getline(line, 800, '"');
					s[3] = line;
					if (s[3].empty()) { succ = false; break; }
				}
				else if (prmt == "-keyword")
				{
					if (!s[4].empty()) { succ = false; break; }
					ss >> s[4];
					if (s[4].empty()) { succ = false; break; }
					if (s[4][0] != '"' || s[4][s[4].length() - 1] != '"') { succ = false; break; }
					s[4] = s[4].substr(1, s[4].length() - 2);
				}
				else if (prmt == "-price")
				{
					if (pr >= 0) { succ = false; break; }
					if (!(ss >> pr) || pr < 0.0) { succ = false; break; }
				}
				else { succ = false; break; }
			}
			if (!succ) { puts("Invalid"); continue; }
			if (!s[1].empty()) select_book.mdy_ISBN(s[1], select_id);
			if (!s[2].empty()) select_book.mdy_name(s[2], select_id);
			if (!s[3].empty()) select_book.mdy_author(s[3], select_id);
			if (!s[4].empty()) select_book.mdy_keyword(s[4], select_id);
			if (pr >= 0.0) select_book.mdy_price(pr, select_id);
		}
		else if (s[0] == "import")
		{
			if (permission < 3) { puts("Invalid"); continue; }
			if (select_id < 0) { puts("Invalid"); continue; }
			double pr;
			int n;
			if (!(ss >> n >> pr)) { puts("Invalid"); continue; }
			ss >> s[1];
			if (!s[1].empty()) { puts("Invalid"); continue; }
			finance::add(-pr);
			select_book.mdy_quantity(n, select_id);
		}
		else if (s[0] == "buy")
		{
			if (permission < 1) { puts("Invalid"); continue; }
			int n;
			if (!(ss >> s[1] >> n)) { puts("Invalid"); continue; }
			if (s[1].empty() || !s[2].empty()) { puts("Invalid"); continue; }

			vector<int> id = search(node(s[1]), 1);
			book abk;
			if (!id.size()) { puts("Invalid"); continue; }
			else abk.get_book(id[0]);

			if (!abk.check(n)) { puts("Invalid"); continue; }
			finance::add(n * abk.get_price());
			abk.mdy_quantity(-n, id[0]);
		}
		else if (s[0] == "show")
		{
			ss >> s[1];
			if (s[1] == "finance")
			{
				if (permission < 7) { puts("Invalid"); continue; }
				int n;
				if (!(ss >> n)) n = INT_MIN;
				ss >> s[2];
				if (!s[2].empty()) { puts("Invalid"); continue; }
				if (n == INT_MIN) finance::putout();
				else if (n <= 0) { puts("Invalid"); continue; }
				else finance::putout(n);
				continue;
			}
			if (permission < 1) { puts("Invalid"); continue; }
			stringstream ssr(line);
			ssr >> s[0]; s[1].clear();
			bool succ = true, hasone = false;
			while (!ssr.eof())
			{
				ssr.getline(line, 800, '=');
				int st = 0;
				while (line[st] == ' ') st++;
				string prmt(line + st);
				if (prmt.empty()) break;
				if (prmt == "-ISBN")
				{
					if (!s[1].empty()) { succ = false; break; }
					ssr >> s[1];
					if (s[1].empty()) { succ = false; break; }
					hasone = true;
				}
				else if (prmt == "-name")
				{
					if (!s[2].empty()) { succ = false; break; }
					ssr.getline(line, 800, '"');
					ssr.getline(line, 800, '"');
					s[2] = line;
					if (s[2].empty()) { succ = false; break; }
					hasone = true;
				}
				else if (prmt == "-author")
				{
					if (!s[3].empty()) { succ = false; break; }
					ssr.getline(line, 800, '"');
					ssr.getline(line, 800, '"');
					s[3] = line;
					if (s[3].empty()) { succ = false; break; }
					hasone = true;
				}
				else if (prmt == "-keyword")
				{
					if (!s[4].empty()) { succ = false; break; }
					ssr >> s[4];
					if (s[4].empty()) { succ = false; break; }
					if (s[4][0] != '"' || s[4][s[4].length() - 1] != '"') { succ = false; break; }
					s[4] = s[4].substr(1, s[4].length() - 2);
					hasone = true;
				}
				else { succ = false; break; }
			}
			if (!succ) { puts("Invalid"); continue; }
			if (!hasone)
			{
				set<book> S;
				for (int i = 0; i < bkn; i++) S.insert(book(i));
				for (auto it = S.begin(); it != S.end(); it++)
				{
					it->out();
				}
				continue;
			}
			vector<int> ans[10];
			for (int i = 1; i <= 4; i++)
			{
				if (s[i].empty()) continue;
				ans[i] = search(node(s[i]), i);
				sort(ans[i].begin(), ans[i].end());
				if (ans[0].empty()) ans[0] = ans[i];
				ans[5] = ans[0];
				ans[0].clear();
				int st = 0;
				for (int j = 0; j < (int)ans[i].size(); j++)
				{
					if (st >= (int)ans[5].size()) break;
					while (ans[5][st] < ans[i][j]) st++;
					if (ans[5][st] == ans[i][j])
					{
						ans[0].push_back(ans[i][j]);
						st++;
					}
				}
				set<book> S;
				for (int i = 0; i < (int)ans[0].size(); i++) S.insert(book(ans[0][i]));
				for (auto it = S.begin(); it != S.end(); it++)
				{
					it->out();
				}
			}

		}
		else if (s[0].empty()) continue;
		else { puts("Invalid"); continue; }
	}
}
