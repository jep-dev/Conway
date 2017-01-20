include ../Maker/Makefile
include Doxygen.mk

$(doc) $(doc_file): Doxygen.mk

override LDLIBS+=-lSDL2_ttf -lSDL2 -ldl
override all_out_files+=$(doc_files)
