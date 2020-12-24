TARGETS := test_poly

.PHONY: all

all: $(TARGETS)


test: $(TARGETS)
	@for test in $(TARGETS); do \
		./$$test; \
	done

test_poly: test_poly.cpp
	@g++ -lpoly -o test_poly test_poly.cpp -std=c++2a

clean:
	-@rm -f $(TARGETS)