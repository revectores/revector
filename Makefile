LIBRARY_NAME = revector
MODULE_NAMES := matrix poly
TEST_PATH = test
SRC_PATH = src

MODULE_DIRS := $(foreach name, $(MODULE_NAMES), $(SRC_PATH)/$(name))
STEMS       := $(foreach name, $(MODULE_NAMES), $(SRC_PATH)/$(name)/$(name))

HEADERS     := $(foreach stem, $(STEMS), $(stem).h)
SOURCES     := $(foreach stem, $(STEMS), $(stem).cpp)
OBJS        := $(foreach stem, $(STEMS), $(stem).o)
SHARED_OBJS := $(foreach name, $(MODULE_NAMES), $(SRC_PATH)/$(name)/lib$(name).so)

TESTS         := $(foreach name, $(MODULE_NAMES), $(TEST_PATH)/test_$(name))
TESTS_SOURCES := $(foreach name, $(TESTS), $(name).cpp)

SYS_INCLUDE_PATH = /usr/local/include
SYS_LIBRARY_PATH = /usr/local/lib

.PHONY: all



all: $(OBJECTS) install

libmatrix.so: $(MATRIX_PATH)/matrix.o
	g++ -shared -o libmatrix.so $(MATRIX_PATH)/matrix.o -std=c++2a

$(SHARED_OBJS): $(OBJS)
	for name in $(MODULE_NAMES); do \
		g++ -shared -o $(SRC_PATH)/$$name/lib$$name.so $(SRC_PATH)/$$name/$$name.o; \
	done

$(OBJS): $(SOURCES)
	for stem in $(STEMS); do \
		g++ -c -fpic -o $$stem.o -c $$stem.cpp -std=c++2a; \
	done

install: $(SHARED_OBJS) $(HEADERS)
	-mkdir $(SYS_INCLUDE_PATH)/$(LIBRARY_NAME)
	-mkdir $(SYS_LIBRARY_PATH)/$(LIBRARY_NAME)

	-cp $(SHARED_OBJS) $(SYS_LIBRARY_PATH)/$(LIBRARY_NAME)
	-cp $(HEADERS) $(SYS_INCLUDE_PATH)/$(LIBRARY_NAME)

	for name in $(MODULE_NAMES); do \
		ln -s $(SYS_LIBRARY_PATH)/$(LIBRARY_NAME)/lib$$name.so $(SYS_LIBRARY_PATH)/lib$$name.so; \
	done

uninstall:
	rm -r $(SYS_INCLUDE_PATH)/$(LIBRARY_NAME)
	rm -r $(SYS_LIBRARY_PATH)/$(LIBRARY_NAME)

test: $(TESTS)
	for test_name in $(TESTS); do \
		$$test_name; \
	done

$(TESTS): $(TEST_SOURCES)
	for name in $(MODULE_NAMES); do \
		g++ -l$$name -o $(TEST_PATH)/test_$$name $(TEST_PATH)/test_$$name.cpp -std=c++2a; \
	done

clean:
	-rm $(OBJS)
	-rm $(SHARED_OBJS)m
	-rm $(TESTS)
