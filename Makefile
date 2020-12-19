OBJECTS = libmatrix.so
TEST_OBJECTS = test/test_matrix
SRC = src
MATRIX_PATH = $(SRC)/matrix

SYS_INCLUDE_PATH = /usr/local/include
SYS_LIBRARY_PATH = /usr/local/lib

.PHONY: all



all: $(OBJECTS) install

libmatrix.so: $(MATRIX_PATH)/matrix.o
	g++ -shared -o libmatrix.so $(MATRIX_PATH)/matrix.o -std=c++2a

$(MATRIX_PATH)/matrix.o: $(MATRIX_PATH)/matrix.cpp
	g++ -c -fpic -o $(MATRIX_PATH)/matrix.o $(MATRIX_PATH)/matrix.cpp -std=c++2a

install: $(MATRIX_PATH)/matrix.h libmatrix.so
	cp $(MATRIX_PATH)/matrix.h $(SYS_INCLUDE_PATH)/matrix.h
	cp libmatrix.so $(SYS_LIBRARY_PATH)/libmatrix.so

uninstall:
	rm $(SYS_INCLUDE_PATH)/matrix.h
	rm $(SYS_LIBRARY_PATH)/libmatrix.so



test: $(TEST_OBJECTS)
	test/test_matrix

test/test_matrix: test/test_matrix.cpp
	g++ -lmatrix -o test/test_matrix test/test_matrix.cpp -std=c++2a

clean:
	-find src -name "*.o" -type f -delete
	-rm $(OBJECTS)
	-rm $(TEST_OBJECTS)

