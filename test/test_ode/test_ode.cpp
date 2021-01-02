#include <cmath>
#include <utility>
#include <iostream>
#include <revector/ode.h>




double func0(const double &x, const double &y){
    return 4 * x / y - x * y;
}
double pfunc0(const double &x, const double &y){
    return 2 * sqrt(1 - exp(-x*x));
}
point_t<double> init_point0 = {1e-10, 1e-10};
interval_t<double> interval0 = {-1e-10, 2};
double step0 = 0.1;



double func1(const double &x, const double &y){
    return x * x - y * y;
}
point_t<double> init_point1 = {-1, 0};
interval_t<double> interval1 = {-1, 0};
double step1 = 0.1;



Vector<double> func2(const Vector<double> &x, const Vector<double> &y){
    return Vector<double>({y[1], -y[0], -y[2]});
}
point_t<Vector<double>> init_point2 = {{0, 0, 0}, {-1, 0, 1}};
interval_t<Vector<double>> interval2 = {{0, 0, 0}, {1, 1, 1}};
double step2 = 0.01;



Vector<double> func3(const Vector<double> &x, const Vector<double> &y){
    return Vector<double>({y[1], 3 * y[1] - 2 * y[0]});
}
point_t<Vector<double>> init_point3 = {{0, 0}, {0, 1}};
interval_t<Vector<double>> interval3 = {{0, 0}, {1, 1}};
double step3 = 0.02;



Vector<double> func4(const Vector<double> &x, const Vector<double> &y){
    return Vector<double>({y[1], 0.1 * (1 - y[0] * y[0]) * y[1] - y[0]});
}
point_t<Vector<double>> init_point4 = {{0, 0}, {1, 0}};
interval_t<Vector<double>> interval4 = {{0, 0}, {1, 1}};
double step4 = 0.1;



Vector<double> func5(const Vector<double> &x, const Vector<double> &y){
    return Vector<double>({y[1], y[0] / (exp(x[0]) + 1)});
}
point_t<Vector<double>> init_point5 = {{0, 0}, {1, 0}};
interval_t<Vector<double>> interval5 = {{0, 0}, {2, 2}};
double step5 = 0.1;



Vector<double> func6(const Vector<double> &x, const Vector<double> &y){
    return Vector<double>({y[1], -sin(y[0])});
}
point_t<Vector<double>> init_point6 = {{0, 0}, {1, 0}};
interval_t<Vector<double>> interval6 = {{0, 0}, {4, 4}};
double step6 = 0.2;




void test_double(){
    FirstOrderODEIVP<double> ode0(func0, init_point0, interval0, step0);
    FirstOrderODEIVP<double> ode1(func1, init_point1, interval1, step1);

    auto xy0 = ode0.forward_Euler_method();
    auto xy1 = ode1.forward_Euler_method();

    auto x0 = xy0.first;
    auto y0 = xy0.second;
    auto x1 = xy1.first;
    auto y1 = xy1.second;

    for (auto v: y0) std::cout << v << " ";
    std::cout << std::endl;
    for (auto v: y1) std::cout << v << " ";
    std::cout << std::endl;
}


void test_vector_double(){
    FirstOrderODEIVP<Vector<double>> ode2(func2, init_point2, interval2, step2);
    FirstOrderODEIVP<Vector<double>> ode3(func3, init_point3, interval3, step3);

    auto xy2 = ode2.forward_Euler_method();

    auto x2 = xy2.second;
    auto y2 = xy2.second;

    for (auto v: y2) std::cout << v << " ";
    std::cout << std::endl;
}


int main(){
    test_double();
    test_vector_double();
    return 0;
}
