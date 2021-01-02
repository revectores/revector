#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

typedef struct __point {
	double x;
	double y;
} point;


class Monomial {
public:
	double coef;
	int exp;

	Monomial() {coef=0; exp=0;}
	Monomial(double _coef) {coef=_coef; exp=0;}
	Monomial(double _coef, int _exp){coef=_coef; exp=_exp;}
	~Monomial(){};

	bool operator==(const Monomial& m) const;
	bool operator!=(const Monomial& m) const;
	Monomial operator+(const Monomial& m) const;
	Monomial operator*(const Monomial& m) const;
    friend std::ostream& operator<< (std::ostream& os, const Monomial &m);
};

class Polynomial {
public:
	std::vector<Monomial> terms;

	Polynomial(): terms(std::vector<Monomial>{}) {}
	Polynomial(Monomial term): terms(std::vector<Monomial>{term}) {}
	Polynomial(std::vector<Monomial> terms_): terms(terms_) {}

	Polynomial sort();
	Polynomial sorted() const;
	bool operator==(const Polynomial& other) const;
	Polynomial operator+(const Monomial& m) const;
	Polynomial operator+(const Polynomial& p) const;
	Polynomial operator*(const Monomial& m) const;
	Polynomial operator*(const Polynomial& p) const;
	double evaluate(double x) const;
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
};



Polynomial Lagrange_interp(const std::vector<point>& points);
Polynomial Newton_interp(const std::vector<point>& points);
