CXX?=g++
RM?=rm

INC?=include/
SRC?=src/
APP?=app/
LIB?=lib/
BIN?=bin/

DIRS?=view model
INC_DIRS?=$(foreach D,$(DIRS),$(INC)$(D))
INCS?=$(foreach I,$(INC_DIRS),-I$(I))

override BINS?=$(BIN)modular
override LIBS?=$(LIB)libframe.so $(LIB)frame.o $(LIB)main.o

override CXXFLAGS+=-std=c++11 \
	-I/usr/include/SDL2/ -I$(INC) $(INCS)
override LDLIBS+=-lSDL2_ttf -lSDL2 -ldl
override LDFLAGS+=-Llib -Wl,-rpath,lib

default: .clang_complete $(BIN)modular

$(BIN)modular: $(LIB)libframe.so $(LIB)main.o
	$(CXX) $(LDFLAGS) \
		-o $(BIN)modular $(LIB)main.o -lframe $(LDLIBS)

$(LIB)libframe.so: $(LIB)frame.o
	$(CXX) $(LDFLAGS) -shared \
		-o $(LIB)libframe.so $(LIB)frame.o $(LDLIBS)

$(LIB)main.o: $(APP)main.cpp
	$(CXX) $(CXXFLAGS) \
		-c -o $(LIB)main.o $(APP)main.cpp

$(LIB)frame.o: $(SRC)view/frame.cpp
	$(CXX) $(CXXFLAGS) -fPIC \
		-c -o $(LIB)frame.o $(SRC)view/frame.cpp

.clang_complete: .phony_explicit
	@echo $(foreach V,$(CXXFLAGS),$(V: %=%)\\n) > $@
#@echo CXXFLAGS=$(CXXFLAGS)
#@echo CXXFLAGS-\>$($(CXXFLAGS) '-I/usr/include':% =%\\n)
#@echo $($(CXXFLAGS) '-I/usr/include':% =%\\n) > $@

clean:
	$(RM) $(BINS) $(LIBS)

.PHONY: clean .phony_explicit
