# New attempt at clean autodependency generation for a modular project
#______________________________________________________________________________

# INPUT FORMATS
HPP_DIR?=include/
TPP_DIR?=$(HPP_DIR)
CPP_DIR?=src/

# OUTPUT FORMATS
OUT_TYPES=O REL_O ABS_O D TD SO EXE
D_DIR?=dep/
TD_DIR?=dep/
O_DIR?=lib/
SO_DIR?=lib/
EXE_DIR?=bin/

#______________________________________________________________________________

# FLAG OVERRIDES
override CXXFLAGS+=-std=c++11 -I/usr/include/SDL2/ -I$(HPP_DIR)
override LDFLAGS+=-L$(SO_DIR) -Wl,-rpath,$(SO_DIR)
override LDLIBS+=-lSDL2_ttf -lSDL2 -ldl

# TOOLS
CXX?=g++
MAKE_D=@mv -f $(TD_DIR)$*.Td $(D_DIR)$*.d && touch $@
MAKE_TD=$(CXX) -MT $@ -MMD -MP -MF $(TD_DIR)$*.Td $(CXXFLAGS)
MAKE_REL_O=$(MAKE_TD) -fPIC -c
MAKE_ABS_O=$(MAKE_TD) -c
MAKE_SO=$(CXX) $(LDFLAGS) -shared
MAKE_EXE=$(CXX) $(LDFLAGS)

#______________________________________________________________________________

EXE_NAME=modular
EXE_SRC_NAME=$(EXE_NAME)_main
EXE_FILE=$(EXE_DIR)$(EXE_NAME)

define MODULE =
$(addprefix $(1)_,$(2))
endef
define WRAP =
$(addprefix $(1),$(addsuffix $(3),$(2)))
endef

ABS_O_NAMES=$(EXE_SRC_NAME)
REL_O_NAMES=$(call MODULE,view,frame panel)
O_NAMES=$(ABS_O_NAMES) $(REL_O_NAMES)
SO_NAMES=$(addprefix lib,$(REL_O_NAMES))

ABS_O_FILES=$(call WRAP,$(O_DIR),$(ABS_O_NAMES),.o)
REL_O_FILES=$(call WRAP,$(O_DIR),$(REL_O_NAMES),.o)
O_FILES=$(ABS_O_FILES) $(REL_O_FILES)
D_FILES=$(call WRAP,$(D_DIR),$(O_NAMES),.d)
TD_FILES=$(call WRAP,$(TD_DIR),$(O_NAMES),.d)
SO_FILES=$(call WRAP,$(SO_DIR),$(SO_NAMES),.so)
SO_LIBS=$(addprefix -l,$(REL_O_NAMES))

default: .clang_complete $(EXE_FILE)

.PHONY: clean clean-bin clean-lib clean-dep debug-% .clang_complete

clean: clean-bin clean-lib clean-dep
clean-bin:; $(RM) $(EXE_FILE)
clean-lib:; $(RM) $(O_FILES) $(SO_FILES)
clean-dep:; $(RM) $(D_FILES) $(TD_FILES)

$(EXE_FILE): $(SO_FILES) $(ABS_O_FILES)
	$(MAKE_EXE) -o $@ $(ABS_O_FILES) $(SO_LIBS) $(LDLIBS)
$(SO_FILES): $(SO_DIR)lib%.so: $(O_DIR)%.o
	$(MAKE_SO) -o $@ $< $(LDLIBS)

define MAKE_O_FILES =
	$($(1)_O_FILES): $(O_DIR)%.o: $(CPP_DIR)%.cpp
endef

$(call MAKE_O_FILES,ABS)
$(call MAKE_O_FILES,ABS)
	$(MAKE_ABS_O) -o $@ $<
	$(MAKE_D)
$(call MAKE_O_FILES,REL)
	$(MAKE_REL_O) -o $@ $<
	$(MAKE_D)

$(D_DIR)%.d:;
.PRECIOUS: $(D_DIR)%.d

.clang_complete:; @echo $(CXXFLAGS) > $@

debug-%:; @echo "#$* = '$($*)'"

include $(wildcard $(D_FILES))
