TARGETS := test_matrix test_eigen

.PHONY: all

all: $(TARGETS)


test: $(TARGETS)
	for test in $(TARGETS); do \
		./$$test; \
	done

test_matrix: test_matrix.cpp
	g++ -lmatrix -o test_matrix test_matrix.cpp -std=c++2a

test_eigen: test_eigen.cpp
	g++ -lmatrix -o test_eigen test_eigen.cpp -std=c++2a

clean:
	-rm $(TARGETS)