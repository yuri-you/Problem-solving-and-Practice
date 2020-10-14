#include <iostream>
#include <vector>
#include<sstream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;

// Implement your selection algorithm. You can add any standard library if needed.
//
void solve(vector<int>& data, int role, int begin, int end) {
    if (begin == end) {
        cout << data[begin];
        return;
    }
    int a = (end-begin) * rand() / (RAND_MAX)+begin;
    int compare = data[a];
    data[a] = data[begin];
    int left = begin, right = end;
    while (left < right) {
        while (data[right] <= compare && left < right)--right;
        if (left < right)data[left] = data[right];
        while (data[left] >= compare && left < right)++left;
        if (left < right)data[right] = data[left];
    }
    data[left] = compare;
    if (left == role) {
        cout << data[left];
        return;
    }
    if (left < role)solve(data, role, left + 1, end);
    else solve(data, role, begin, left - 1);
    return;
}




int main() {
    // Input processing.
    string str;
    getline(cin, str);
    stringstream str1(str);
    int get;
    vector<int> data;
    while (str1 >> get) {
        data.push_back(get);
    }
    int role;
    cin >> role;
    solve(data, role - 1, 0, data.size() - 1);
    // select the target and print the results.


    return 0;
}
