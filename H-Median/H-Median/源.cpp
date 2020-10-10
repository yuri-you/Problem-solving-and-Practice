#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;
void sort1(vector<int>& number,int left,int right) {
	if (left >= right)return;
	int tmp = number[left],left1=left,right1=right;
	while (left1 < right1) {
		while (number[right1] <= tmp && left1 < right1) --right1;
		if (left1 < right1)number[left1] = number[right1];
		while (number[left1] >= tmp&& left1 < right1)++left1;
		if (left1 < right1)number[right1] = number[left1];
	}
	number[left1] = tmp;
	sort1(number, left, left1 - 1);
	sort1(number, left1 + 1, right);
}
class Solution {
public:
	float hMedian(vector<int>& citations) {
		//code here!!
		int a = citations.size();
		sort1(citations,0,a-1);
		int i = a;
		for (; i >0; --i) {
			if (i <= citations[i - 1])break;
		}
		if (i % 2)return citations[i/2];
		else {
			return (double(citations[i / 2]) + double(citations[i / 2 - 1])) / 2;
		}
	}
};

int main(int argc, char** argv) {
	std::string line;
	int number;
	std::vector<int> numbers;

	std::getline(std::cin, line);
	std::istringstream stream(line);
	while (stream >> number)
		numbers.push_back(number);

	Solution s;
	float res = s.hMedian(numbers);

	std::cout << std::fixed;
	std::cout << std::setprecision(1) << res << endl;

	return 0;
}
