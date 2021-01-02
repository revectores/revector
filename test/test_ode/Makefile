TARGETS := test_ode

.PHONY: all

all: $(TARGETS)


test: $(TARGETS)
	for test in $(TARGETS); do \
		./$$test; \
	done

test_ode: test_ode.cpp
	g++ -lode -o test_ode test_ode.cpp -std=c++2a

clean:
	-rm $(TARGETS)