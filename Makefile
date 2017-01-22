complete_name?=
complete_ext?=.clang_complete
complete_file?=$(complete_name)$(complete_ext)
bak_ext?=.bak
complete_backup?=$(complete_file)$(bak_ext)

include ../Maker/Makefile
include Doxygen.mk

$(doc) $(doc_file): Doxygen.mk

override LDLIBS+=-lSDL2_ttf -lSDL2 -ldl
override all_out_files+=$(doc_files)

$(complete_file):
	@echo $(foreach V,$(CXXFLAGS),$(V)\\n) > $@
