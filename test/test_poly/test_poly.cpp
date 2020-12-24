#include <cstdio>
#include <revector/poly.h>

void test_poly_mul(){
	Polynomial factor1(std::vector<Monomial> {Monomial(1, 3), Monomial(2, 5)});
	Polynomial factor2(std::vector<Monomial> {Monomial(2, 5), Monomial(1, 3)});
	Polynomial product(std::vector<Monomial> {Monomial(4, 10), Monomial(4, 8), Monomial(1, 6)});
	assert(factor1 * factor2 == product);
}


int main(){
	test_poly_mul();
	printf("test_poly passed.\n");
	return 0;
}
