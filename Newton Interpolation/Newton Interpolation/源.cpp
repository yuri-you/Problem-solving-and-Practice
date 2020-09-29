#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;


// You can add additional standard libraries if necessary.
// Implement the Newton interpolation!
class Newton {
public:
    Newton(vector<double> x, vector<double> y) : X(x), Y(y) {}
    double ans(double x) {
        double h = X[1] - X[0];
        int max = X.size();
        double ans=0;
        double x_1 = 1;
        for (int i = 0; i < max-1; ++i) {
            ans += Y[0];
            for (int j = 0; j < max - i - 1; ++j) {
                Y[j] = (Y[j + 1] - Y[j])*(x-X[i]) / (i + 1) / h;
            }
        }
        ans += Y[0];
        return ans;
    }


private:
    vector<double> X, Y;
};


// Test your implementation.
int main(int argc, const char* argv[]) {
    //  Input preprocessing.
    string str;
    getline(cin, str);
    stringstream xstr(str);
    getline(cin, str);
    stringstream ystr(str);

    // X and Y are two vectors of equal length to be traversed.
    vector<double> X, Y;
    double a;
    while (xstr >> a)
        X.push_back(a);
    while (ystr >> a)
        Y.push_back(a);
    Newton data(X, Y);
    // interp_x is the point to be interpolated.
    double interp_x;
    cin >> interp_x;
    double ans = data.ans(interp_x);
    printf("%.3f", ans);
    // Do Newton interpolation for interp_x using X and Y, and print your results
    // Note: The result retains three decimal places (rounded)!



    // End
    return 0;
}
