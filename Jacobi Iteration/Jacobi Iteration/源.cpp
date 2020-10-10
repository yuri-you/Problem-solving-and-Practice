#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <algorithm>
//#include <fstream>
using namespace std;
class NO_SOLOTION {};
class NO_UNIQUE_SOLUTION {};
class NO_COVERGE {};
const double eps = 1e-8;
const double inaccurate = 1e-8;
const double stop = 1e-5;
int Rank(vector<vector<double>> w)
{
    int row = 0;
    int line = w.size(), c = w[0].size();
    for (int i = 0; i < c; ++i) //i th column
    {
        int t = row;
        for (int j = row + 1; j < line; ++j)
            if (fabs(w[j][i]) > fabs(w[t][i]))
                t = j;
        if (fabs(w[t][i]) < eps)
            continue;
        if (t != row)
            swap(w[t], w[row]);
        for (int j = row + 1; j < line; ++j)
        {
            double t = w[j][i] / w[i][i];
            for (int k = i; k < c; ++k)
                w[j][k] -= w[i][k] * t;
        }
        if (++row >= min(line, c))
            break;
    }
    return row;
}
void judge(vector<vector<double>> data, int size) {
    vector<vector<double>> another = data;
    for (int i = 0; i < size; ++i) {
        another[i].pop_back();
    }
    int a1 = Rank(data), a2 = Rank(another);
    if (a2 < size) {
        if (a2 == a1)throw NO_UNIQUE_SOLUTION();
        else throw NO_SOLOTION();
    }
    else return;
}
// Implement your Jacobi Iteration algorithm.
// You can add any standard library if needed.
//
void initial(vector<vector<double>> &a) {
    for (int i = 0; i < a.size(); ++i) {
        double tmp = a[i][i];
        if (fabs(tmp) < eps) {
            for (int k = 0; k < a.size(); ++k) {
                if (k == i)continue;
                if (fabs(a[k][i]) > eps) {
                    for (int m = 0; m <=a.size(); ++m) {
                        a[i][m] += a[k][m];
                    }
                    tmp = a[i][i];
                    break;
                }
            }
        }
        for (int j = 0; j <= a.size(); ++j) {
            a[i][j] /= tmp;
        }
    }
}
vector<double> jaccobi(vector<vector<double>> data, vector<double> x) {
    vector<double> ans;
    int size = data.size();
    for (int i = 0; i < size; ++i) {
        double count = data[i][size];
        for (int j = 0; j < data.size(); ++j) {
            if (i == j)continue;
            count -= data[i][j] * x[j];
        }
        ans.push_back(count / data[i][i]);
    }
    return ans;
}
vector<double> jaccobi(vector<vector<double>> data,int j1) {
    int size = data.size();
    initial(data);
    vector<double> x;
    vector<double> x1;
    for (int i = 0; i < size; ++i) {
        x.push_back(j1);
    }
    bool signal;
    int iterations = 1e6;
    while (iterations--) {
        x1 = x;
        x = jaccobi(data, x1);
        signal = false;
        for (int i = 0; i < size; ++i) {
            if (fabs(x1[i] - x[i]) > stop) {
                signal = true;
               
            }
        }
        if (!signal) {
            return x;
        }
    }
    throw NO_COVERGE();
}
vector<double> gauss(vector<vector<double>>& data) {
    int times =data.size() + 1;//ап
    vector<double> ans;
    for (int i = 0; i < times - 2; ++i) {
        if (fabs(data[i][i]) < inaccurate) {
            for (int j = i + 1; j < times - 1; ++j) {
                if (fabs(data[j ][i]) > inaccurate) {
                    for (int k = 0; k < times; ++k) {
                        data[i ][ k] += data[j][ k];
                    }
                    break;
                }
            }
        }
        for (int j = i + 1; j < times - 1; ++j) {
            if (fabs(data[j][i]) > inaccurate) {
                double rate = (data[j][i] / data[i][i]);
                for (int k = 0; k < times; ++k) {
                    data[j][k] -= data[i][k] * rate;
                }
            }
        }
    }
    for (int i = times - 2; i >= 0; --i) {
        if (fabs(data[i][i]) < inaccurate) {
            if (fabs(data[i ][times - 1]) > inaccurate) throw NO_SOLOTION();
            else throw NO_UNIQUE_SOLUTION();
        }
        else {
            ans.push_back(data[i ][times - 1] / data[i][i]);
            for (int j = 0; j < i; ++j) {
                double rate = data[j][i] / data[i][i];
                for (int k = 0; k < times; ++k) {
                    data[j][k] -= data[i][k] * rate;
                }
            }
        }
    }
    return ans;
}



// Test your implementation.
int main() {
    // Input processing.
    string ptr;
    getline(cin, ptr);
    stringstream str(ptr);
    vector<double> line;
    vector<vector<double>> data;
    double a;
    while (str >> a) {
        line.push_back(a);
    }
    int size = line.size()-1;
    data.push_back(line);
    for (int i = 0; i < size - 1; ++i) {
        line.clear();
        getline(cin, ptr);
        str = stringstream(ptr);
        while (str >> a) {
            line.push_back(a);
        }
        data.push_back(line);
    }
    try {
         judge(data, size);
    }
    catch (NO_SOLOTION wrong) {
        printf("No solution!");
    }
    catch (NO_UNIQUE_SOLUTION wrong) {
        printf("No unique solution!");
    }
    int m = 0;
    while (1-(++m)) {
        try {
            vector<double> m1 = jaccobi(data,m);
            for (int i = 0; i < size; ++i) {
                printf("%.3f ", m1[i]);
            }
            return 0;
        }
        catch (NO_COVERGE) {

        }
    }
    // Solve the linear system and print the results.
    return 0;
}
