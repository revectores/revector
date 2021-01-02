#pragma once
#include <cmath>
#include <vector>
#include <utility>
#include "vector.h"


template <typename T>
using func_t = T (*)(const T &x, const T &y);

template <typename T>
using vector_pair = std::pair<std::vector<T>, std::vector<T>>;

template <typename T>
struct point_t {
    T x;
    T y;
};

template <typename T>
struct interval_t {
    T left;
    T right;
    T len(){
        return right - left;
    }
};

template <typename T>
T min(T a, T b){
    return a < b ? a : b;
}

template<typename T>
T get_zero(T x){
    return x + (-x);
}

template<typename T>
T get_uint(T x){
    T zero = get_zero(x);
    T unit = ++zero;
    return unit;
}


template<typename T>
class FirstOrderODE {
protected:
    func_t<T> f;

public:
    FirstOrderODE(func_t<T> f_): f(f_) {};
};


template<typename T>
class FirstOrderODERange: FirstOrderODE<T> {
protected:
    interval_t<T> xrange;
    interval_t<T> yrange;
};



template<typename T>
class FirstOrderODEIVP: FirstOrderODE<T> {
protected:
    using FirstOrderODE<T>::f;
    point_t<T> init_point;
    interval_t<T> interval;
    double step;

    std::vector<T> x;
    std::vector<T> y;
    T zero;
    T unit;

public:
    FirstOrderODEIVP(func_t<T> f_, point_t<T> init_point_, interval_t<T> interval_, double step_):
    FirstOrderODE<T>(f_), init_point(init_point_), interval(interval_), step(step_),
    zero(get_zero(init_point.x)), unit(zero + 1) {
        values_init();
        std::cout << "unit: " << unit << std::endl;
        std::cout << "step: " << step << std::endl;
    }

    vector_pair<T> values_init();
    vector_pair<T> forward_Euler_method();
    vector_pair<T> backward_Euler_method();
    vector_pair<T> Runge_Kutta(size_t order);
    vector_pair<T> Adams_expl(size_t order);
    vector_pair<T> Adams_impl(size_t order);
};




template <typename T>
vector_pair<T> FirstOrderODEIVP<T>::values_init(){
    T xi(init_point.x);

    for (size_t i = 1; xi <= interval.right; i++){
        x.push_back(xi);
        xi = init_point.x + step * unit * i;
    }

    y = std::vector<T>(x.size(), get_zero(init_point.y));
    y[0] = init_point.y;
    return {x, y};
}


template <typename T>
vector_pair<T> FirstOrderODEIVP<T>::forward_Euler_method(){
    for (int i = 0; i < y.size() - 1; i++){
        y[i+1] = y[i] + step * f(x[i], y[i]);
    }
    std::cout << "x.back(): " << x.back() << std::endl;

    return {x, y};
}


template <typename T>
vector_pair<T>  FirstOrderODEIVP<T>::Runge_Kutta(size_t order){
    switch (order){
    case 2:
        for (size_t i = 0; i < y.size() - 1; i++){
            T k1 = f(x[i], y[i]);
            T k2 = f(x[i] + step, y[i] + step * k1);
            y[i+1] = y[i] + step / 2 * (k1 + k2);
        }
        break;
    case 3:
        for (size_t i = 0; i < y.size() - 1; i++){
            T k1 = f(x[i], y[i]);
            T k2 = f(x[i] + step / 2, y[i] + step / 2 * k1);
            T k3 = f(x[i] + step, y[i] - step * k1 + 2 * step * k2);
        }
        break;
    case 4:
        for (size_t i = 0; i < y.size() - 1; i++){
            T k1 = f(x[i], y[i]);
            T k2 = f(x[i] + step / 2, y[i] + step / 2 * k1);
            T k3 = f(x[i] + step / 2, y[i] + step / 2 * k2);
            T k4 = f(x[i] + step, y[i] + step * k3);
            y[i+1] = y[i] + step / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
        }
        break;
    }
    return {x, y};
}


template <typename T>
vector_pair<T> FirstOrderODEIVP<T>::Adams_expl(size_t order){
    if (y[min(order, y.size())] == zero){
        Runge_Kutta(order);
    }

    switch(order){
    case 2:
        for (size_t i = 1; i < y.size() - 1; i++){
            T k0 =  3 * f(x[i], y[i]);
            T k1 = -1 * f(x[i-1], y[i-1]);
            y[i+1] = y[i] + step / 2 * (k0 + k1);
        }
        break;
    case 3:
        for (size_t i = 2; i < y.size() - 1; i++){
            T k0 =  23 * f(x[i], y[i]);
            T k1 = -16 * f(x[i-1], y[i-1]);
            T k2 =   5 * f(x[i-2], y[i-2]);
            y[i+1] = y[i] + step / 12 * (k0 + k1 + k2);
        }
        break;
    case 4:
        for (size_t i = 3; i < y.size() - 1; i++){
            T k0 =  55 * f(x[i], y[i]);
            T k1 = -59 * f(x[i-1], y[i-1]);
            T k2 =  37 * f(x[i-2], y[i-2]);
            T k3 =  -9 * f(x[i-3], y[i-3]);
            y[i+1] = y[i] + step / 24 * (k0 + k1 + k2 + k3);
        }
        break;
    }
    return {x, y};
}


template <typename T>
vector_pair<T> FirstOrderODEIVP<T>::Adams_impl(size_t order){
    Runge_Kutta(order);

    switch(order){
    case 2:
        for (size_t i = 0; i < y.size() - 1; i++){
            T k0 = f(x[i+1], y[i+1]);
            T k1 = f(x[i], y[i]);
            y[i+1] = y[i] + step / 2 * (k0 + k1);
        }
        break;
    case 3:
        for (size_t i = 0; i < y.size() - 1; i++){
            T k0 =  5 * f(x[i+1], y[i+1]);
            T k1 =  8 * f(x[i], y[i]);
            T k2 = -1 * f(x[i-1], y[i-1]);
            y[i+1] = y[i] + step / 12 * (k0 + k1 + k2);
        }
        break;
    case 4:
        for (size_t i = 0; i < y.size() - 1; i++){
            T k0 =  9 * f(x[i+1], y[i+1]);
            T k1 = 19 * f(x[i], y[i]);
            T k2 = -5 * f(x[i-1], y[i-1]);
            T k3 =  1 * f(x[i-2], y[i-2]);
            y[i+1] = y[i] + step / 24 * (k0 + k1 + k2 + k3);
        }
        break;
    }
    return {x, y};
}
