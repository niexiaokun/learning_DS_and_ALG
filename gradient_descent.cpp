#include <bits/stdc++.h>

using namespace std;

inline double f(double x) {
    return pow(x - 2.5, 2) - 1;
}

inline double df(double x) {
    return 2 * x - 5;
}

inline double calculate_gradient(const function<double(double)>& f, double x, double epsilon = 1e-8){
    return (f(x + epsilon) - f(x - epsilon)) / (2 * epsilon);
}

void gradient_descent(const function<double(double)>& f,
                      const function<double(double)>& df,
                      double init, double lr, int n_iters = 1e4, double epsilon = 1e-8) {
    double x = init;
    double last_x = x;
    int step = 0;
    while (step < n_iters) {
        printf("step %d : x = %f\n", step, x);
        double gradient = df(x);
        last_x = x;
        x = x - lr * gradient;
        if (abs(f(x) - f(last_x)) < epsilon)
            break;
        ++step;
    }
    printf("final x = %f, last_x = %f\n", x, last_x);
}

int main(int argc, char* argv[]) {

    gradient_descent(f, df, 0, 0.1);

    cout << df(3.69) << "  " << calculate_gradient(f, 3.69) << endl;

    return 0;
}