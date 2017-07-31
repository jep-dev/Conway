include Makefile.conf
# ................................................................ Definitions
#                                                                      %_files
complete_files=$(ccomplete)
exe_files=$(exes:%=$(exe_dir)%)
a_files=$(libs:%=$(so_dir)lib%.a)
so_files=$(libs:%=$(so_dir)lib%.so)
d_files=$(exes:%=$(d_dir)%.d) $(libs:%=$(d_dir)%.d)
o_files=$(exes:%=$(o_dir)%.o) $(libs:%=$(so_dir)%.o)
out_files=$(foreach X,exe so d o,$($(X)_files))

#......................................................................Targets
default: $(exe_dir)$(build_app)
#                                                                      Compile
$(exes:%=$(o_dir)%.o): \
$(o_dir)%.o: $(cpp_dir)%.cpp $(wildcard $(hpp_dir)%.hpp) $(d_files)
	$(CXX) $(CXXFLAGS) \
		$(flags_decl) \
		$(flags_d) \
		-c $< \
		-o $@
	$(move_d)
$(libs:%=$(so_dir)%.o): \
$(so_dir)%.o: $(cpp_dir)%.cpp \
$(wildcard $(foreach X,hpp tpp,$($(X)_dir)%.$(X))) $(d_files)
	$(CXX) $(CXXFLAGS) -c -fPIC \
		$(flags_decl) \
		$(flags_d) \
		-o $@ \
		$<
	$(move_d)
#                                                                         Link
lib%.so: %.o
	$(CXX) $(LDFLAGS) -shared \
		$< \
		-o $@ $(LDLIBS)
# lib%.a: %.o
# 	$(CXX) $(LDFLAGS) \
# 		$< \
# 		-o $@ $(LDLIBS)
$(exes:%=$(exe_dir)%): \
$(exe_dir)%: $(o_dir)%.o $(so_files) $(o_files)
	$(CXX) $(LDFLAGS) \
		-Wl,-rpath,$(o_dir):$(so_dir):$(so_o_dir) \
		-o $@ $< \
		$(libs:%=-l%) $(LDLIBS)
#............................................................. Special targets
#                                                               Clang Complete
$(ccomplete): $(d_files); @echo $(CXXFLAGS) > $@
.PRECIOUS: $(complete_files)
#                                                                  Print value
print-val-%:; @echo "$*"
#                                                     Print variable and value
print-var-%:; @echo "'$*' = '$($*)'"
#                                                               Print includes
# Does not appear to show included dependency files
print-includes: print-var-MAKEFILE_LIST
.PHONY: echo-% print-%

#                                                                      clean-%
clean-testing-%:; echo 'rm -f -i' $($(@)_files)
clean-o:; rm -f $(o_files)
clean-d:; rm -f $(d_files)
clean-so:; rm -f $(so_files)
clean-a:; rm -f $(a_files)
clean-exe:; rm -f $(exe_files)
clean: clean-o clean-d clean-so clean-a clean-exe
.PHONY: clean $(foreach T,o d so a exe,clean-$(T))

#                                                             Precious targets
.PRECIOUS: $(d_dir)%.d .clang_complete
$(d_dir)%.d:;

#........................................................ Dependency inclusion
include $(wildcard $($(libs) $(exes):%=release/dep/%.d))
include $(wildcard Doxygen.mk)
