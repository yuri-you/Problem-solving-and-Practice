#include<iostream>
#include<bitset>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<cmath>
using namespace std;
typedef bitset<16>  bit;
long double x, xsinx;
int sizeofvec;
long double trans(bit a) {
	long double ans = -1;
	long double add = 8;
	int k = 0;
	for (add=8,k=0;k < 16; ++k, add /= 2) {
		if (a[15 - k]) {
			ans += add;
		}
	}
	return ans;
}
class number {
public:
	bit a;
	long double value() {
		long double tmp = trans(a);
		return -tmp * sin(tmp);
	};
	number(bit a1):a(a1) {
	}
	friend bool operator<(number, number);
};
bool operator<(number a1,number a2) {
	return a1.value() < a2.value();
}

//bool operator>(bit a1, bit a2) {
//	int k = 16;
//	while(k--) {
//		if (a1[k] > a2[k])
//			return true;
//		else {
//			if (a1[k] < a2[k])
//				return false;
//		}
//	}
//	return false;
//}

bit init() {
	return (rand() * 2) % (1 << 16);
}
vector<bit> initial() {
	vector<bit> ans;
	int k = sizeofvec;
	while (k--) {
		ans.push_back(init());
	}
	return ans;
}
void mutation(vector<bit>& data) {
	int k = data.size();
	while (k--) {
		int m = 16;
		while (m--) {
			if (!(rand() % (1 << 10)))
				data[k][m].flip();
		}
	}
	return;
}
void binary(vector<bit>& data) {
	int k = data.size() / 2;
	for (int i = 0; i < k; ++i) {
		int a = rand() % 16;
		bit m1 = data[2 * i], m2 = data[2 * i + 1];
		bool t1 = m1[a];
		m1[a] = m2[a], m2[a] = t1;
		data.push_back(m1);
		data.push_back(m2);
	}
}
void choose(vector<bit>& data) {
	priority_queue<number> queue;
	int size = data.size();
	for (bit m : data)
		queue.push(m);
	data.clear();
	number tmp = queue.top();
	if (-tmp.value() < xsinx) {
		xsinx = -tmp.value();
		x = trans(tmp.a);
	}
	for (int i = 0; i < size/2; ++i) {
		data.push_back(queue.top().a);
		queue.pop();
	}
	return;
}
void generator(vector<bit>& data, int generate) {
	if (generate < 0)return;
	mutation(data);
	binary(data);
	choose(data);
	generator(data, generate-1);
}
int main() {
	srand(time(0));
	xsinx = 0;
	int gen;
	cin >> gen>>sizeofvec;
	vector<bit> a = initial();
	generator(a, gen);
	cout << x;
	return 0;
}