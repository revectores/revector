#include "poly.h"
#include "cmath"


bool Monomial::operator==(const Monomial& m) const {
	return (coef == m.coef) && (exp == m.exp);
}


bool Monomial::operator!=(const Monomial& m) const {
	return !(*this == m);
}


Monomial Monomial::operator+(const Monomial& m) const {
	// assert(exp == m.exp);
    return Monomial(coef + m.coef, exp);
}


Monomial Monomial::operator*(const Monomial& m) const {
    return Monomial(coef * m.coef, exp + m.exp);
}


std::ostream& operator<<(std::ostream& os, const Monomial& m){
	if (m.coef == 0){
		return os;
	}

	if (m.coef > 0) {
		os << "+";
	}

	os << std::setprecision(10) << std::fixed << m.coef << "x^" << m.exp;
    return os;
}


Polynomial Polynomial::sort(){
	std::sort(terms.begin(), terms.end(), [](Monomial m1, Monomial m2) {return m1.exp > m2.exp;});
	return *this;
}


Polynomial Polynomial::sorted() const {
	Polynomial sorted_poly = Polynomial(*this);
	return sorted_poly.sort();
}


bool Polynomial::operator==(const Polynomial& other) const {
	Polynomial sorted_this  = this->sorted();
	Polynomial sorted_other = other.sorted();

	if (sorted_this.terms.size() != sorted_other.terms.size()){
		return false;
	}

	for (int i = 0; i < sorted_this.terms.size(); i++){
		if (sorted_this.terms[i] != sorted_other.terms[i]) return false;
	}

	return true;
}


Polynomial Polynomial::operator+(const Monomial& m) const {
	std::vector<Monomial> sum_terms = terms;
	for (auto it = sum_terms.begin(); it != sum_terms.end(); it++){
		if (it->exp == m.exp) {
			it->coef += m.coef;
			return Polynomial(sum_terms);
		}
	}
	sum_terms.push_back(m);
	return Polynomial(sum_terms);
}


Polynomial Polynomial::operator+(const Polynomial& p) const {
	Polynomial sum = terms;
	for (auto it = p.terms.begin(); it != p.terms.end(); it++){
		sum = sum + (*it);
	}
	return sum;
}


Polynomial Polynomial::operator*(const Monomial& m) const {
	std::vector<Monomial> product_terms;
	for (auto it = terms.begin(); it != terms.end(); it++){
		product_terms.push_back((*it) * m);
	}
	return Polynomial(product_terms);
}


Polynomial Polynomial::operator*(const Polynomial& p) const {
	Polynomial product;
	for (auto it = p.terms.begin(); it != p.terms.end(); it++){
		product = product + (*this) * (*it);
	}
	return product;
}


std::ostream& operator<<(std::ostream& os, const Polynomial& p){
	for (auto it = p.terms.begin(); it != p.terms.end(); it++){
		std::cout << *it << " ";
	}
    return os;
}


double Polynomial::evaluate(double x) const {
	double sum = 0;
	for (auto term_it = terms.begin(); term_it != terms.end(); term_it++){
		sum += term_it->coef * std::pow(x, term_it->exp);
	}
	return sum;
} 


Polynomial Lagrange_interp(const std::vector<point>& points){
	Polynomial Lagrange_interp_polynomial {};

	int n = points.size();
	for (int k=0; k < n; k++){
		Polynomial product {std::vector<Monomial> {1, 0}};
		for (int i=0; i < n; i++){
			if (i == k) continue;
			Polynomial term {{{1, 1}, {-points[i].x, 0}}};
			term = term * (1.0 / (points[k].x - points[i].x));
			// std::cout << "k=" << k << "i=" << i << "term=" << term << std::endl;
			product = product * term;
		}
		product = product * points[k].y;
		// std::cout << "product=" << product << std::endl;
		Lagrange_interp_polynomial = Lagrange_interp_polynomial + product;
	}

	Lagrange_interp_polynomial.sort();
	return Lagrange_interp_polynomial;
}


Polynomial Newton_interp(const std::vector<point>& points){
	Polynomial Newton_interp_polynomial {};

	int n = points.size();
	for (int k=1; k <= n; k++){
		double diff = 0;
		for (int i=0; i < k; i++){
			double denominator = 1;
			for (int j=0; j < k; j++){
				if (i==j) continue;
				denominator *= (points[i].x - points[j].x);
			}
			diff += points[i].y / denominator;
		}

		Polynomial prod {std::vector<Monomial> {1, 0}};
		for (int j=0; j<k-1; j++){
			Polynomial term {{{1, 1}, {-points[j].x, 0}}};
			prod = prod * term;
		}

		Newton_interp_polynomial = Newton_interp_polynomial + prod * diff;
	}

	Newton_interp_polynomial.sort();
	return Newton_interp_polynomial;
}
