#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include<fstream>
using namespace std;


// You can add additional standard libraries if necessary.
// Implement the Lagrange interpolation!
class Lagrange {
public:
    Lagrange(vector<double> x, vector<double> y) : X(x), Y(y) {
        int size = X.size();
        for (int i = 0; i < size; ++i) {
            double z = 1;
            for (int j = 0; j < size; ++j) {
                if (j == i)continue;
                z *= x[i] - x[j];
            }
            Z.push_back(y[i] / z);
        }
    }
    double get(double interp_x) {
        double all = 1,ans=0;
        int size = X.size();
        //for (int i = 0; i < size; ++i) {
        //    all *= (interp_x - X[i]);
        //}
        for (int i = 0; i < size; ++i) {
            double tmp = 1;
            for (int j = 0; j < size; ++j) {
                if (i == j)continue;
                tmp *= (interp_x - X[j]);
            }
            ans += tmp * Z[i];
        }
        return ans;
    }
private:
    vector<double> X, Y, Z;
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
    Lagrange data(X, Y);
    // interp_x is the point to be interpolated.
    double interp_x;
    cin >> interp_x;
    double ans = data.get(interp_x);
    // Do Lagrange interpolation for interp_x using X and Y, and print your results
    // Note: The result retains three decimal places (rounded)!
    printf("%.3lf",ans);


    // End
    return 0;
}
