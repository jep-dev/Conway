include ../Maker/Makefile
include ../Maker/clang_complete.mk
include Doxygen.mk

$(doc) $(doc_file): Doxygen.mk

override LDLIBS+=-lSDL2_ttf -lSDL2 -ldl
override all_out_files+=$(doc_files)
