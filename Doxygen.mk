# Tools

doxygen?=doxygen
doxymake=$(doxygen) -g

# Input parameters

DOXY_PROJECT_NAME?="Modular"
DOXY_PROJECT_BRIEF?="\"Experimental modular project\""
doc_dir?=doc/
doc_name?=Doxyfile
doc_file?=$(doc_dir)$(doc_name)
doc_sentinel?=$(doc_file:$(doc_dir)%=$(doc_dir).%.sen)

DOXY_BUILTIN_STL_SUPPORT?=YES
DOXY_CALL_GRAPH?=YES
DOXY_COLS_IN_ALPHA_INDEX?=5
DOXY_DOT_TRANSPARENT?=YES
DOXY_EXTRACT_ALL?=YES
DOXY_EXTRACT_PRIVATE?=YES
DOXY_EXTRACT_PACKAGE?=YES
DOXY_GENERATE_MAN?=YES
DOXY_OUTPUT_DIRECTORY=$(doc_dir)
DOXY_QT_AUTOBRIEF?=YES
DOXY_RECURSIVE?=NO
DOXY_SHOW_INCLUDE_FILES?=YES
DOXY_STRIP_FROM_PATH?=../
DOXY_USE_MDFILE_AS_MAINPAGE?=README.md

override DOXY_INPUT+=$(DOXY_USE_MDFILE_AS_MAINPAGE) \
	$(foreach V,HPP TPP CPP,$(wildcard $($(V)_DIR)*$($(V)_EXT)))

V_HEADERS=$(filter %$(HPP_EXT) %$(TPP_EXT),$(DOXY_INPUT))
V_DOXY_ALL=$(filter DOXY_%,$(.VARIABLES))
V_DOXY_ALL_SUFFIXES=$(V_DOXY_ALL:DOXY_%=%)
V_DOXY_REPLACEMENT=$(foreach V,$(V_DOXY_ALL_SUFFIXES),\\n$(V) = $(DOXY_$(V)))

$(doc_sentinel): $(doc_file) $(EXE_FILE)
	@$(doxygen) $(doc_file) >/dev/null && touch $@

$(doc_file):
	@$(doxymake) $(doc_file) >/dev/null && \
		echo $(V_DOXY_REPLACEMENT) >> $(doc_file)

doc: $(doc_sentinel)
clean-doc:; $(RM) $(doc_file) $(doc_sentinel)
