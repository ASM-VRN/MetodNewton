#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double newtonMethod(double (*f)(double), double (*df)(double), double x0, double epsilon, int maxIterations);

bool containsEps(std::vector<double>& vec, double x, double eps);

vector<double> findRoots(double (*f)(double), double (*df)(double), double (*df2)(double), double lowerBound, double higherBound, double precision = 1E-4) {
    vector<double> list;
    double i = lowerBound;
    double step = precision * 100;
    while (i + step <= higherBound) {
        double root = newtonMethod(f, df, i, precision, 1000);
        if (isnan(root)) {
            i += step;
            continue;
        }
        if (root < lowerBound || root > higherBound) {
            i += step;
            continue;
        }
        if (!containsEps(list, root, precision)) {
            list.push_back(root);
        }
        i += step;
    }
    return list;
}

bool containsEps(vector<double>& vec, double x, double eps) {
    for (double i : vec) {
        if (abs(i - x) < eps) {
            return true;
        }
    }
    return false;
}

double newtonMethod(double (*f)(double), double (*df)(double), double x0, double epsilon, int maxIterations) {
    double x = x0;
    int i = 0;
    while (i < maxIterations) {
        double fx = f(x);
        double dfx = df(x);
        if (abs(fx) < epsilon) {
            return x;
        }
        x -= fx / dfx;
        i++;
    }
    return nan("");
}

double f(double x) {
    return sin(x) - tan(x) * cos(2 * x) + 1;
}

double df(double x) {
    return cos(x) - (1 / (cos(x) * cos(x))) * cos(2 * x) + 2 * sin(2 * x) * tan(x);
}

double df2(double x) {
    return -2 * sin(x) - 2 * sin(2 * x) / (cos(x) * cos(x)) + 2 * sin(2 * x) * tan(x) +
        2 * (1 / (cos(x) * cos(x))) * (cos(x) * cos(2 * x) - sin(x) * sin(2 * x));
}

int main() {
    vector<double> roots = findRoots(f, df, df2, 1.0, 6.0);
    for (double root : roots) {
        cout << root << " ";
    }
    return 0;
}