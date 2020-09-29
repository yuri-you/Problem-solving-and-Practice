//#include "std_lib_facilities.h"
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
class Divide_zero {
};
class Wrong_express {
};
double expression();
double term();
double primary();


// Start here!
double expression()
{
    double left = term();
    while (true) {
        char a = getchar();
        double right;
        while (a == ' ')a = getchar();
        switch (a) {
        case ';':return left;
        case '+': {right = term(); left += right; break;
        case '-':right = term(); left -= right; break;
        case ')':cin.putback(a); return left;
        }
        }
    }
    // please implement here!
    //
}

double term()
{
    double left = primary();
    while (true) {
        char a = getchar();
        double right;
        while (a == ' ')a = getchar();
        switch (a) {
        case '*':right = primary(); left *= right; break;
        case '/':right = primary(); if (!right)throw Divide_zero(); else left /= right; break;
        default:cin.putback(a); return left;
        }
    }
    // please implement here!
    //

}

double primary()
{
    char a = getchar();
    while (a == ' ')a = getchar();
    if (a == '(') {
        double left = expression();
        a = getchar();
        while (a == ' ')a = getchar();
        if (a != ')')throw Wrong_express();
        else return left;
    }
    else {
        if (a == '-') {
            a = getchar();
            while (a == ' ')a = getchar();
            if (a == '(') {
                double answer = expression();
                a = getchar();
                while (a == ' ')a = getchar();
                if (a != ')')throw Wrong_express();
                else return -answer;
            }
            else if (isdigit(a) || a == '.') {
                cin.putback(a);
                double answer;
                cin >> answer;
                return -answer;
            }
            else throw Wrong_express();
        }
        else {
            cin.putback(a);
            double answer;
            cin >> answer;
            return answer;
        }
    }
}


// main function
int main()
{
    double val = 0;
    try {
        val = expression();
        printf("%.3f", val);
    }
    catch (Divide_zero a) {
        cout << "divide by zero";
    }
    catch (Wrong_express a) {
        cout << "wrong_expression";
    }
    return 0;
}
