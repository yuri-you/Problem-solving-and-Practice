#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
class Solution {
public:
	int nthUglyNumber(int n) {
		priority_queue<ll, deque<ll>, greater<ll> > q;
		q.push(1);
		ll j;
		while (n--) {
			j = q.top();
			q.pop();
			while (!q.empty() && j == q.top())q.pop();
			if (2 * j)q.push(2 * j);
			//2147483647
			if (3 * j)q.push(3 * j);
			if (5 * j)q.push(5 * j);
		}
		return j;
	}
};

int main() {
	Solution s;
	int n;
	cin >> n;
	cout << s.nthUglyNumber(n) << endl;
	return 0;
}