// Add any standard library if needed.
#include <iostream>
#include<sstream>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;
struct p {
    int number;
    int left, right;
    p(int number1, int left1, int right1) :number(number1), left(left1), right(right1) {}
    p() {}
    bool operator<(const p& other) {
        return number < other.number;
    }
    bool operator>(const p& other) {
        return number > other.number;
    }
    void operator=(const p& other) {
        number = other.number;
        left = other.left;
        right = other.right;
    }

};
template<class T>
class prior_queue {
private:
    T* data;
    long long maxsize;
    long long currentsize;
    void doublesize() {
        maxsize <<= 1;
        T* tmp = new T[maxsize];
        for (long long i = 0; i < currentsize; ++i) {
            tmp[i] = data[i];
        }
        delete[]data;
        data = tmp;
    }
    void percolateDown(long long position) {
        if (((position << 1) + 1) >= currentsize)return;
        long long change = (position << 1) + 1;
        if (((change + 1) < currentsize) && data[change + 1] < data[change])++change;
        if (data[position] > data[change]) {
            T tmp = data[position];
            data[position] = data[change];
            data[change] = tmp;
            percolateDown(change);
        }
    }
public:
    prior_queue() {
        currentsize = 0;
        maxsize = 2;
        data = new T[maxsize];
    }
    prior_queue(T* arr, long long length) {
        currentsize = length;
        maxsize = currentsize << 1;
        data = new T[maxsize];
        for (long long i = 0; i < length; ++i) {
            data[i] = arr[i];
        }
        for (long long i = (length >> 1) - 1; i >= 0; --i) {
            percolateDown(i);
        }
    }
    ~prior_queue(){ delete[]data; }
    T pop() {
        T tmp = data[0];
        data[0] = data[--currentsize];
        percolateDown(0);
        return tmp;
    }
    void push(const T& a) {
        if (currentsize == maxsize)doublesize();
        ++currentsize;
        long long hole = currentsize - 1;
        while (hole > 0 && data[((hole - 1) >> 1)] > a) {
            data[hole] = data[((hole - 1) >> 1)];
            --hole;
            hole >>= 1;
        }
        data[hole] = a;
    }
    bool empty() {
        return currentsize == 0;
    }
};
//using std::cin;
//using std::cout;
//using std::string;
//using std::vector;
//using std::stringstream;
//using std::shared_ptr;

int* connect;
// Implement your minimum spinning tree algorithm
int father(int i) {
    if (connect[i] == i)return i;
    else return connect[i] = father(connect[i]);
}
void link(int i, int j) {
    int i1 = father(i), i2 = father(j);
    if (i1 > i2)swap(i1, i2);
    connect[i2] = i1;
}
int solve(prior_queue<p>& prior,int size) {
    connect = new int[size];
    for (int i = 0; i < size; ++i) {
        connect[i] = i;
    }
    int ans = 0;
    p fetch;
    while (!prior.empty()) {
        fetch = prior.pop();
        while (!prior.empty() && father(fetch.left)==father(fetch.right)) {
            fetch = prior.pop();
        }
        if (prior.empty())break;
        link(fetch.left, fetch.right);
        ans += fetch.number;
    }
    return ans;
}




// Test your implementation
int main() {
    prior_queue<p> prior;
    string read1;
    getline(cin, read1);
    int a, times = 0;
    stringstream read2(read1);
    while (read2 >> a) {
        if (a != 0)
            prior.push(p(a, 0, times));
        ++times;
    }
    for (int i = 1; i < times; ++i) {
        getline(cin, read1);
        stringstream read3(read1);
        int j = 0;
        while (read3 >> a) {
            if (a != 0&&i<j)
                prior.push(p(a, i, j));
            ++j;
        }
    }
    cout << solve(prior, times);
    return 0;
}