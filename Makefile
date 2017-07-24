# .................................................................... Options
# TODO migrate options or everything but options to another makefile
builds=release
exes=modular
libs=runnable driver frame panel events
#                                                                      build_%
build_name?=release
build_app?=modular
build_version?=0.1
#                                                                        %_dir
build_dir?=$(build_name)/
exe_dir?=$(build_dir)bin/
so_dir?=$(build_dir)lib/
d_dir?=$(build_dir)dep/
so_o_dir?=$(build_dir)lib/
exe_o_dir?=$(build_dir)obj/
cpp_dir?=src/
tpp_dir?=impl/
hpp_dir?=include/
#                                                                       %_dirs
inc_dirs?=$(tpp_dir) $(hpp_dir)
src_dirs?=$(cpp_dir) $(inc_dirs)
lib_dirs?=$(exe_o_dir) $(so_dir) $(so_o_dir)
# .................................................................. Overrides
flags_sdl=-D_REENTRANT -I/usr/include/SDL2
flags_d=-MT $@ -MMD -MP -MF $(d_dir)$*.Td
flags_decl=$(inc_dirs:%=-I%) \
	-D'BUILD="$(build_name)"' -D'VERSION=$(build_version)'
libs_sdl=-lSDL2_ttf -lSDL2
libs_exe=$(libs:%=-l%)
override CXXFLAGS+=-std=c++11 $(flags_decl) $(flags_sdl)
override LDFLAGS+=$(lib_dirs:%=-L%)
override LDLIBS+=$(libs_sdl) -ldl

# ................................................................ Definitions
move_d=mv -f $(d_dir)$*.Td $(d_dir)$*.d && touch $@
#                                                                      %_files
ccomplete=.clang_complete
complete_files=$(ccomplete)
exe_files=$(exes:%=$(exe_dir)%)
so_files=$(libs:%=$(so_dir)lib%.so)
d_files=$(exes:%=$(d_dir)%.d) $(libs:%=$(d_dir)%.d)
o_files=$(exes:%=$(exe_o_dir)%.o) $(libs:%=$(so_o_dir)%.o)
out_files=$(foreach X,exe so d o,$($(X)_files))

#......................................................................Targets
default: $(exe_files)
#                                                                      Compile
$(libs:%=$(so_o_dir)%.o): \
$(so_o_dir)%.o: $(cpp_dir)%.cpp $(hpp_dir)%.hpp
	$(CXX) $(CXXFLAGS) $(flags_d) \
		-fPIC -c -o $@ $<
	$(move_d)
$(exes:%=$(exe_o_dir)%.o): \
$(exe_o_dir)%.o: $(cpp_dir)%.cpp $(d_files)
	$(CXX) $(CXXFLAGS) $(flags_d) \
		-c -o $@ $<
	$(move_d)
#                                                                         Link
$(libs:%=$(so_dir)lib%.so): \
$(so_dir)lib%.so: $(so_o_dir)%.o $(foreach D,d hpp,$($(D)_dir)%.$(D))
	$(CXX) $(LDFLAGS) \
		-shared -o $@ $< $(LDLIBS)
$(exes:%=$(exe_dir)%): \
$(exe_dir)%: $(exe_o_dir)%.o $(so_files) $(o_files)
	$(eval build_app:=$(@:$(exe_o_dir)%=%))
	$(CXX) $(LDFLAGS) \
		-Wl,-rpath,$(exe_o_dir):$(so_dir):$(so_o_dir) \
		-o $@ $< \
		$(libs:%=-l%) $(LDLIBS)
#                                                               Clang Complete
$(ccomplete): $(d_files); @echo $(CXXFLAGS) > $@
.PRECIOUS: $(complete_files)

#............................................................. Special targets
#                                                                  Print value
print-val-%:; @echo "$*"
#                                                     Print variable and value
print-var-%:; @echo "'$*' = '$($*)'"
#                                                               Print includes
# Does not appear to show included dependency files
print-includes: print-var-MAKEFILE_LIST
.PHONY: echo-% print-%

#                                                                      clean-%
clean-o:; rm -f $(o_files)
clean-d:; rm -f $(d_files)
clean-so:; rm -f $(so_files)
clean-exe:; rm -f $(exe_files)
clean: clean-o clean-d clean-so clean-exe
.PHONY: clean $(foreach T,o d so exe,clean-$(T))

#                                                             Precious targets
.PRECIOUS: $(d_dir)%.d .clang_complete
$(d_dir)%.d:;

#........................................................ Dependency inclusion
include $(wildcard $($(libs) $(exes):%=release/dep/%.d))
include $(wildcard Doxygen.mk)
