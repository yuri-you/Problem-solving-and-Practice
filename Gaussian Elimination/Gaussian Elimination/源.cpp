#include <iostream>
#include <vector>
#include<cmath>
using namespace std;
class NO_SOLOTION {};
class NO_UNIQUE_SOLUTION {};
double inaccurate = 1e-7;
vector<double> solve(vector<double>& data) {
    int times = sqrt(data.size())+1;//ап
    vector<double> ans;
    for (int i = 0; i < times-2; ++i) {
        if (fabs(data[i*times+i])<inaccurate) {
            for (int j = i+1; j < times-1; ++j) {
                if (fabs(data[j*times+i]) > inaccurate) {
                    for (int k = 0; k < times; ++k) {
                        data[i * times + k] += data[j * times + k];
                    }
                    break;
                }
            }
        }
        for (int j = i + 1; j < times-1; ++j) {
            if (fabs(data[j*times+i]) > inaccurate) {
                double rate = (data[j * times + i] / data[i * times + i]);
                for (int k = 0; k < times; ++k) {
                    data[j*times+k] -= data[i*times+k] *rate ;
                }
            }
        }
    }
    for (int i = times - 2; i >=0; --i) {
        if (fabs(data[i * times + i]) < inaccurate) {
            if (fabs(data[i * times + times-1]) > inaccurate) throw NO_SOLOTION();
            else throw NO_UNIQUE_SOLUTION();
        }
        else {
            ans.push_back(data[i * times + times-1] / data[i * times + i]);
            for (int j = 0; j < i; ++j) {
                double rate = data[j * times + i] / data[i * times + i];
                for (int k = 0; k < times; ++k) {
                    data[j*times+k] -= data[i*times+k] *rate;
                }
            }
        }
    }
    return ans;
}



// Test your implementation.
int main() {
    // Input processing.
    double c=1;
    vector<double> data;
    while (c!=-73) {
        cin >> c;
        data.push_back(c);
    }
    // Solve the linear system and print the results.
    try {
        vector<double>ans=solve(data);
        for (int i = 0; i < ans.size(); ++i) {
            printf("%.3f ", ans[ans.size()-i-1]);
        }
    }
    catch (NO_SOLOTION wrong) {
        printf("No solution!");
    }
    catch (NO_UNIQUE_SOLUTION wrong) {
        printf("No unique solution!");
    }
    return 0;
}
