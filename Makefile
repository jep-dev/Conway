# Print only output lines, use `make ... | grep '\-o '
# Just library outputs: `make ... | grep '\-fPIC\|\-shared'
#_____________________________________________________________________ Options
builds=release
exes=modular
libs=frame
#                                                                      build_%
build_name?=release
build_version?=0.1
#                                                                        sdl_%
sdl_cxx?=-D_REENTRANT -I/usr/include/SDL2
sdl_ld?=-lSDL2
#                                                                    overrides
override CXXFLAGS+=-DVERSION=$(build_version) -DBUILD=$(build_name) \
	-std=c++11 -Iinclude/release -Iimpl/release -Iinclude -Iimpl $(sdl_cxx)
override LDFLAGS+=-Lrelease/lib -Lrelease/obj -Lobj $(sdl_ld)
override LDLIBS+=-lSDL2_ttf -lSDL2 -ldl
#______________________________________________________ Generated target lists
#                                                                  exe_%_files
exe_files=$(exes:%=$(build_name)/bin/%)
exe_o_files=$(exes:%=$(build_name)/obj/%.o)
exe_d_files=$(exes:%=$(build_name)/dep/%.d)
#                                                                    so_%_file
so_files=$(libs:%=$(build_name)/lib/lib%.so)
so_o_files=$(libs:%=$(build_name)/lib/%.o)
so_d_files=$(libs:%=$(build_name)/dep/%.d)
#                                                                  all_%_files
all_exe_files=$(exe_files)
all_so_files=$(so_files)
all_o_files=$(exe_o_files) $(so_o_files)
all_d_files=$(exe_d_files) $(so_d_files)
all_out_files=$(all_exe_files) $(all_so_files) $(all_o_files) $(all_d_files)
#_____________________________________________________________________ Targets
#                                                                      default
default: $(all_exe_files) #                                            default
#                                                                Echo variable
echo-%: print-"$* = '$($*)'"
#                                                                   Echo value
print-%:; @echo "$*"
#_________________________________________________________________ Definitions
#                                                                      %_dep #
define add_dep =
	-MT $@ -MMD -MP -MF release/dep/$*.Td
endef
define move_dep =
	@mv -f release/dep/$*.Td release/dep/$*.d && touch $@
endef
#_____________________________________________________________ Derived Targets
$(exe_files): release/bin/%: release/obj/%.o $(so_files) $(exe_o_files)
	$(CXX) $(LDFLAGS) -Wl,-rpath,release/lib \
		-o $@ $< \
		$(libs:%=-l%) $(LDLIBS)
$(so_files): release/lib/lib%.so: release/lib/%.o
	$(CXX) $(LDFLAGS) \
		-shared -o $@ $< \
		$(LDLIBS)
release/lib/%.o: src/%.cpp
$(so_o_files): release/lib/%.o: src/%.cpp release/dep/%.d include/%.hpp
	$(CXX) $(call add_dep) \
		$(CXXFLAGS) \
		-fPIC -c -o $@ $<
	$(call move_dep)
release/obj/%.o: src/release/%.cpp
$(exe_o_files): release/obj/%.o: src/release/%.cpp release/dep/%.d
	$(CXX) $(call add_dep) \
		$(CXXFLAGS) \
		-c -o $@ $<
	$(call move_dep)

#_______________________________________________________________ Phony targets
.PHONY: clean $(foreach T,o d so exe,clean-$(T)) print-% echo-%
#                                                                    clean-% #
clean-o:; rm -f $(all_o_files)
clean-d:; rm -f $(all_d_files)
clean-so:; rm -f $(all_so_files)
clean-exe:; rm -f $(all_exe_files)

#____________________________________________________________ Precious targets
.PRECIOUS: release/dep/%.d .clang_complete
#                                                              Empty targets #
release/dep/%.d:;
.clang_complete:; @echo $(CXXFLAGS) > .clang_complete #       Clang Complete #
#________________________________________________________ Dependency inclusion
include $(wildcard $($(libs) $(exes):%=release/dep/%.d))
# include $(wildcard Doxygen.mk)                            TODO: when updated
