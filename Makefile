LIBRARY_NAME = revector
MODULE_NAMES := matrix poly
SRC_PATH = src

MODULE_DIRS := $(foreach name, $(MODULE_NAMES), $(SRC_PATH)/$(name))
STEMS       := $(foreach name, $(MODULE_NAMES), $(SRC_PATH)/$(name)/$(name))

HEADERS     := $(foreach stem, $(STEMS), $(stem).h)
SOURCES     := $(foreach stem, $(STEMS), $(stem).cpp)
OBJS        := $(foreach stem, $(STEMS), $(stem).o)
SHARED_OBJS := $(foreach name, $(MODULE_NAMES), $(SRC_PATH)/$(name)/lib$(name).so)

TEST_PATH = test
TEST_DIRS := $(foreach name, $(MODULE_NAMES), $(TEST_PATH)/test_$(name))

SYS_INCLUDE_PATH = /usr/local/include
SYS_LIBRARY_PATH = /usr/local/lib

.PHONY: all .FORCE
.SILENT: clean


all: $(OBJECTS) install

libmatrix.so: $(MATRIX_PATH)/matrix.o
	g++ -shared -o libmatrix.so $(MATRIX_PATH)/matrix.o -std=c++2a

$(SHARED_OBJS): $(OBJS)
	@for name in $(MODULE_NAMES); do \
		g++ -shared -o $(SRC_PATH)/$$name/lib$$name.so $(SRC_PATH)/$$name/$$name.o; \
	done

$(OBJS): $(SOURCES)
	@for stem in $(STEMS); do \
		g++ -c -fpic -o $$stem.o -c $$stem.cpp -std=c++2a; \
	done

install: $(SHARED_OBJS) $(HEADERS)
	-@mkdir -p $(SYS_INCLUDE_PATH)/$(LIBRARY_NAME)
	-@mkdir -p $(SYS_LIBRARY_PATH)/$(LIBRARY_NAME)

	-@cp $(SHARED_OBJS) $(SYS_LIBRARY_PATH)/$(LIBRARY_NAME)
	-@cp $(HEADERS) $(SYS_INCLUDE_PATH)/$(LIBRARY_NAME)

	-@for name in $(MODULE_NAMES); do \
		ln -sf $(SYS_LIBRARY_PATH)/$(LIBRARY_NAME)/lib$$name.so $(SYS_LIBRARY_PATH)/lib$$name.so; \
	done

uninstall:
	-@rm -rf $(SYS_INCLUDE_PATH)/$(LIBRARY_NAME)
	-@rm -rf $(SYS_LIBRARY_PATH)/$(LIBRARY_NAME)

test: $(TEST_MAKEFILES) .FORCE
	@for test_dir in $(TEST_DIRS); do \
		cd $$test_dir; make test; cd - > /dev/null;\
	done

clean:
	-rm -f $(OBJS)
	-rm -f $(SHARED_OBJS)
	@for test_dir in $(TEST_DIRS); do \
		cd $$test_dir; make clean; cd - > /dev/null;\
	done

.FORCE:
