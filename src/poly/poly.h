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

	bool operator==(const Monomial& m);
	bool operator!=(const Monomial& m);
	Monomial operator+(const Monomial& m);
	Monomial operator*(const Monomial& m);
    friend std::ostream& operator<< (std::ostream& os, const Monomial &m);
};

bool term_cmp(Monomial term1, Monomial term2);

class Polynomial {
public:
	std::vector<Monomial> terms;

	Polynomial(): terms(std::vector<Monomial>{}) {}
	Polynomial(Monomial term): terms(std::vector<Monomial>{term}) {}
	Polynomial(std::vector<Monomial> terms_): terms(terms_) {}

	Polynomial sort();
	Polynomial sorted() const;
	bool operator==(const Polynomial& other);
	Polynomial operator+(const Monomial& m);
	Polynomial operator+(const Polynomial& p);
	Polynomial operator*(const Monomial& m);
	Polynomial operator*(const Polynomial& p);
	double evaluate(double x);
	friend std::ostream& operator<<(std::ostream& os, const Polynomial &p);
};



Polynomial Lagrange_interp(std::vector<point> points);
Polynomial Newton_interp(std::vector<point> points);

