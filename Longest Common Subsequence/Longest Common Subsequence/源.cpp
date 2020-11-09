#include<iostream>
#include<string>
#include<vector>
#include<set>

using namespace std;

class unit{
public:
	set<string> str;
	int len;
	unit(int l = -1) :len(l) {};
};
void set_unit(unit** data, string& X, string& Y,int x,int y) {
	if (x == 0 && y == 0) {
		data[0][0].len = 0;
		return;
	}
	if (x && data[x - 1][y].len == -1)
		set_unit(data, X, Y, x - 1, y);
	if (y && data[x][y - 1].len == -1)
		set_unit(data, X, Y, x, y - 1);
	if (x == 0) {
		if (X[0] == Y[y]) {
			string tmp;
			tmp.push_back(X[0]);
			data[x][y].str.insert(tmp);
			data[x][y].len = 1;
		}
		else {
			data[x][y] = data[x][y - 1];
		}
	}
	else {
		if (y == 0) {
			if (Y[0] == X[x]) {
				string tmp;
				tmp.push_back(Y[0]);
				data[x][y].str.insert(tmp);
				data[x][y].len = 1;
			}
			else {
				data[x][y] = data[x - 1][y];
			}
		}
		else {
			if (X[x] == Y[y]) {
				data[x][y].len = data[x - 1][y - 1].len +1;
				for (string str : data[x - 1][y - 1].str) {
					str.push_back(X[x]);
					data[x][y].str.insert(str);
				}
				if (data[x - 1][y - 1].str.empty()) {
					string tmp;
					tmp.push_back(X[x]);
					data[x][y].str.insert(tmp);
				}
			}
			else {
				int l1 = data[x - 1][y].len, l2 = data[x][y - 1].len;
				if (l1 < l2) {
					data[x][y] = data[x][y - 1];
				}
				else {
					data[x][y] = data[x - 1][y];
					if (l1 == l2) {
						for (string str:data[x][y - 1].str) {
							data[x][y].str.insert(str);
						}
					}
				}
			}
		}
	}
	return;
}
set<string> LCS(string X, string Y)
{
	int length1 = X.length(), length2 = Y.length();
	unit *tmp=new unit[length1 * length2];
	unit** data = new unit* [length1];
	for (int i = 0; i < length1; ++i)
		data[i] = &(tmp[i * length2]);
	set_unit(data, X, Y, length1-1, length2-1);
	set<string> ans;
	for (string str : data[length1 - 1][length2 - 1].str)
		ans.insert(str);
	return ans;
}

int main()
{
	string X, Y;
	cin >> X;
	cin >> Y;

	set<string> lcs = LCS(X, Y);

	// print set elements
	for (string str : lcs)
		cout << str << endl;

	return 0;
}