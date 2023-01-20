# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/net/cremi/ymaabout/Bureau/projet techno L2/takuzu-11c"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/autofs/unityaccount/cremi/ymaabout/Bureau/projet techno L2/takuzu-11c"

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/usr/bin/ctest --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test

.PHONY : test/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/autofs/unityaccount/cremi/ymaabout/Bureau/projet techno L2/takuzu-11c/CMakeFiles" "/autofs/unityaccount/cremi/ymaabout/Bureau/projet techno L2/takuzu-11c//CMakeFiles/progress.marks"
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/autofs/unityaccount/cremi/ymaabout/Bureau/projet techno L2/takuzu-11c/CMakeFiles" 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named game

# Build rule for target.
game: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 game
.PHONY : game

# fast build rule for target.
game/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/build
.PHONY : game/fast

#=============================================================================
# Target rules for targets named game_test_juruch

# Build rule for target.
game_test_juruch: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 game_test_juruch
.PHONY : game_test_juruch

# fast build rule for target.
game_test_juruch/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_test_juruch.dir/build.make CMakeFiles/game_test_juruch.dir/build
.PHONY : game_test_juruch/fast

#=============================================================================
# Target rules for targets named game_text

# Build rule for target.
game_text: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 game_text
.PHONY : game_text

# fast build rule for target.
game_text/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_text.dir/build.make CMakeFiles/game_text.dir/build
.PHONY : game_text/fast

#=============================================================================
# Target rules for targets named ContinuousSubmit

# Build rule for target.
ContinuousSubmit: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ContinuousSubmit
.PHONY : ContinuousSubmit

# fast build rule for target.
ContinuousSubmit/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ContinuousSubmit.dir/build.make CMakeFiles/ContinuousSubmit.dir/build
.PHONY : ContinuousSubmit/fast

#=============================================================================
# Target rules for targets named ContinuousMemCheck

# Build rule for target.
ContinuousMemCheck: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ContinuousMemCheck
.PHONY : ContinuousMemCheck

# fast build rule for target.
ContinuousMemCheck/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ContinuousMemCheck.dir/build.make CMakeFiles/ContinuousMemCheck.dir/build
.PHONY : ContinuousMemCheck/fast

#=============================================================================
# Target rules for targets named game_test_ymaabout

# Build rule for target.
game_test_ymaabout: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 game_test_ymaabout
.PHONY : game_test_ymaabout

# fast build rule for target.
game_test_ymaabout/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_test_ymaabout.dir/build.make CMakeFiles/game_test_ymaabout.dir/build
.PHONY : game_test_ymaabout/fast

#=============================================================================
# Target rules for targets named ContinuousConfigure

# Build rule for target.
ContinuousConfigure: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ContinuousConfigure
.PHONY : ContinuousConfigure

# fast build rule for target.
ContinuousConfigure/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ContinuousConfigure.dir/build.make CMakeFiles/ContinuousConfigure.dir/build
.PHONY : ContinuousConfigure/fast

#=============================================================================
# Target rules for targets named ExperimentalSubmit

# Build rule for target.
ExperimentalSubmit: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ExperimentalSubmit
.PHONY : ExperimentalSubmit

# fast build rule for target.
ExperimentalSubmit/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ExperimentalSubmit.dir/build.make CMakeFiles/ExperimentalSubmit.dir/build
.PHONY : ExperimentalSubmit/fast

#=============================================================================
# Target rules for targets named ExperimentalMemCheck

# Build rule for target.
ExperimentalMemCheck: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ExperimentalMemCheck
.PHONY : ExperimentalMemCheck

# fast build rule for target.
ExperimentalMemCheck/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ExperimentalMemCheck.dir/build.make CMakeFiles/ExperimentalMemCheck.dir/build
.PHONY : ExperimentalMemCheck/fast

#=============================================================================
# Target rules for targets named ExperimentalTest

# Build rule for target.
ExperimentalTest: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ExperimentalTest
.PHONY : ExperimentalTest

# fast build rule for target.
ExperimentalTest/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ExperimentalTest.dir/build.make CMakeFiles/ExperimentalTest.dir/build
.PHONY : ExperimentalTest/fast

#=============================================================================
# Target rules for targets named NightlyUpdate

# Build rule for target.
NightlyUpdate: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 NightlyUpdate
.PHONY : NightlyUpdate

# fast build rule for target.
NightlyUpdate/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/NightlyUpdate.dir/build.make CMakeFiles/NightlyUpdate.dir/build
.PHONY : NightlyUpdate/fast

#=============================================================================
# Target rules for targets named NightlyStart

# Build rule for target.
NightlyStart: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 NightlyStart
.PHONY : NightlyStart

# fast build rule for target.
NightlyStart/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/NightlyStart.dir/build.make CMakeFiles/NightlyStart.dir/build
.PHONY : NightlyStart/fast

#=============================================================================
# Target rules for targets named NightlyMemoryCheck

# Build rule for target.
NightlyMemoryCheck: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 NightlyMemoryCheck
.PHONY : NightlyMemoryCheck

# fast build rule for target.
NightlyMemoryCheck/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/NightlyMemoryCheck.dir/build.make CMakeFiles/NightlyMemoryCheck.dir/build
.PHONY : NightlyMemoryCheck/fast

#=============================================================================
# Target rules for targets named NightlyBuild

# Build rule for target.
NightlyBuild: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 NightlyBuild
.PHONY : NightlyBuild

# fast build rule for target.
NightlyBuild/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/NightlyBuild.dir/build.make CMakeFiles/NightlyBuild.dir/build
.PHONY : NightlyBuild/fast

#=============================================================================
# Target rules for targets named game_test_argomes

# Build rule for target.
game_test_argomes: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 game_test_argomes
.PHONY : game_test_argomes

# fast build rule for target.
game_test_argomes/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_test_argomes.dir/build.make CMakeFiles/game_test_argomes.dir/build
.PHONY : game_test_argomes/fast

#=============================================================================
# Target rules for targets named ExperimentalUpdate

# Build rule for target.
ExperimentalUpdate: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ExperimentalUpdate
.PHONY : ExperimentalUpdate

# fast build rule for target.
ExperimentalUpdate/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ExperimentalUpdate.dir/build.make CMakeFiles/ExperimentalUpdate.dir/build
.PHONY : ExperimentalUpdate/fast

#=============================================================================
# Target rules for targets named ContinuousBuild

# Build rule for target.
ContinuousBuild: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ContinuousBuild
.PHONY : ContinuousBuild

# fast build rule for target.
ContinuousBuild/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ContinuousBuild.dir/build.make CMakeFiles/ContinuousBuild.dir/build
.PHONY : ContinuousBuild/fast

#=============================================================================
# Target rules for targets named Continuous

# Build rule for target.
Continuous: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Continuous
.PHONY : Continuous

# fast build rule for target.
Continuous/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Continuous.dir/build.make CMakeFiles/Continuous.dir/build
.PHONY : Continuous/fast

#=============================================================================
# Target rules for targets named Experimental

# Build rule for target.
Experimental: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Experimental
.PHONY : Experimental

# fast build rule for target.
Experimental/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Experimental.dir/build.make CMakeFiles/Experimental.dir/build
.PHONY : Experimental/fast

#=============================================================================
# Target rules for targets named ExperimentalConfigure

# Build rule for target.
ExperimentalConfigure: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ExperimentalConfigure
.PHONY : ExperimentalConfigure

# fast build rule for target.
ExperimentalConfigure/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ExperimentalConfigure.dir/build.make CMakeFiles/ExperimentalConfigure.dir/build
.PHONY : ExperimentalConfigure/fast

#=============================================================================
# Target rules for targets named NightlyTest

# Build rule for target.
NightlyTest: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 NightlyTest
.PHONY : NightlyTest

# fast build rule for target.
NightlyTest/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/NightlyTest.dir/build.make CMakeFiles/NightlyTest.dir/build
.PHONY : NightlyTest/fast

#=============================================================================
# Target rules for targets named NightlyCoverage

# Build rule for target.
NightlyCoverage: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 NightlyCoverage
.PHONY : NightlyCoverage

# fast build rule for target.
NightlyCoverage/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/NightlyCoverage.dir/build.make CMakeFiles/NightlyCoverage.dir/build
.PHONY : NightlyCoverage/fast

#=============================================================================
# Target rules for targets named ExperimentalCoverage

# Build rule for target.
ExperimentalCoverage: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ExperimentalCoverage
.PHONY : ExperimentalCoverage

# fast build rule for target.
ExperimentalCoverage/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ExperimentalCoverage.dir/build.make CMakeFiles/ExperimentalCoverage.dir/build
.PHONY : ExperimentalCoverage/fast

#=============================================================================
# Target rules for targets named NightlyMemCheck

# Build rule for target.
NightlyMemCheck: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 NightlyMemCheck
.PHONY : NightlyMemCheck

# fast build rule for target.
NightlyMemCheck/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/NightlyMemCheck.dir/build.make CMakeFiles/NightlyMemCheck.dir/build
.PHONY : NightlyMemCheck/fast

#=============================================================================
# Target rules for targets named ContinuousStart

# Build rule for target.
ContinuousStart: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ContinuousStart
.PHONY : ContinuousStart

# fast build rule for target.
ContinuousStart/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ContinuousStart.dir/build.make CMakeFiles/ContinuousStart.dir/build
.PHONY : ContinuousStart/fast

#=============================================================================
# Target rules for targets named NightlySubmit

# Build rule for target.
NightlySubmit: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 NightlySubmit
.PHONY : NightlySubmit

# fast build rule for target.
NightlySubmit/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/NightlySubmit.dir/build.make CMakeFiles/NightlySubmit.dir/build
.PHONY : NightlySubmit/fast

#=============================================================================
# Target rules for targets named ContinuousCoverage

# Build rule for target.
ContinuousCoverage: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ContinuousCoverage
.PHONY : ContinuousCoverage

# fast build rule for target.
ContinuousCoverage/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ContinuousCoverage.dir/build.make CMakeFiles/ContinuousCoverage.dir/build
.PHONY : ContinuousCoverage/fast

#=============================================================================
# Target rules for targets named Nightly

# Build rule for target.
Nightly: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Nightly
.PHONY : Nightly

# fast build rule for target.
Nightly/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Nightly.dir/build.make CMakeFiles/Nightly.dir/build
.PHONY : Nightly/fast

#=============================================================================
# Target rules for targets named NightlyConfigure

# Build rule for target.
NightlyConfigure: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 NightlyConfigure
.PHONY : NightlyConfigure

# fast build rule for target.
NightlyConfigure/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/NightlyConfigure.dir/build.make CMakeFiles/NightlyConfigure.dir/build
.PHONY : NightlyConfigure/fast

#=============================================================================
# Target rules for targets named ExperimentalStart

# Build rule for target.
ExperimentalStart: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ExperimentalStart
.PHONY : ExperimentalStart

# fast build rule for target.
ExperimentalStart/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ExperimentalStart.dir/build.make CMakeFiles/ExperimentalStart.dir/build
.PHONY : ExperimentalStart/fast

#=============================================================================
# Target rules for targets named ContinuousTest

# Build rule for target.
ContinuousTest: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ContinuousTest
.PHONY : ContinuousTest

# fast build rule for target.
ContinuousTest/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ContinuousTest.dir/build.make CMakeFiles/ContinuousTest.dir/build
.PHONY : ContinuousTest/fast

#=============================================================================
# Target rules for targets named ContinuousUpdate

# Build rule for target.
ContinuousUpdate: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ContinuousUpdate
.PHONY : ContinuousUpdate

# fast build rule for target.
ContinuousUpdate/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ContinuousUpdate.dir/build.make CMakeFiles/ContinuousUpdate.dir/build
.PHONY : ContinuousUpdate/fast

#=============================================================================
# Target rules for targets named ExperimentalBuild

# Build rule for target.
ExperimentalBuild: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 ExperimentalBuild
.PHONY : ExperimentalBuild

# fast build rule for target.
ExperimentalBuild/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/ExperimentalBuild.dir/build.make CMakeFiles/ExperimentalBuild.dir/build
.PHONY : ExperimentalBuild/fast

game.o: game.c.o

.PHONY : game.o

# target to build an object file
game.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game.c.o
.PHONY : game.c.o

game.i: game.c.i

.PHONY : game.i

# target to preprocess a source file
game.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game.c.i
.PHONY : game.c.i

game.s: game.c.s

.PHONY : game.s

# target to generate assembly for a file
game.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game.c.s
.PHONY : game.c.s

game_aux.o: game_aux.c.o

.PHONY : game_aux.o

# target to build an object file
game_aux.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game_aux.c.o
.PHONY : game_aux.c.o

game_aux.i: game_aux.c.i

.PHONY : game_aux.i

# target to preprocess a source file
game_aux.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game_aux.c.i
.PHONY : game_aux.c.i

game_aux.s: game_aux.c.s

.PHONY : game_aux.s

# target to generate assembly for a file
game_aux.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game_aux.c.s
.PHONY : game_aux.c.s

game_ext.o: game_ext.c.o

.PHONY : game_ext.o

# target to build an object file
game_ext.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game_ext.c.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_text.dir/build.make CMakeFiles/game_text.dir/game_ext.c.o
.PHONY : game_ext.c.o

game_ext.i: game_ext.c.i

.PHONY : game_ext.i

# target to preprocess a source file
game_ext.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game_ext.c.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_text.dir/build.make CMakeFiles/game_text.dir/game_ext.c.i
.PHONY : game_ext.c.i

game_ext.s: game_ext.c.s

.PHONY : game_ext.s

# target to generate assembly for a file
game_ext.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game_ext.c.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_text.dir/build.make CMakeFiles/game_text.dir/game_ext.c.s
.PHONY : game_ext.c.s

game_test_argomes.o: game_test_argomes.c.o

.PHONY : game_test_argomes.o

# target to build an object file
game_test_argomes.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_test_argomes.dir/build.make CMakeFiles/game_test_argomes.dir/game_test_argomes.c.o
.PHONY : game_test_argomes.c.o

game_test_argomes.i: game_test_argomes.c.i

.PHONY : game_test_argomes.i

# target to preprocess a source file
game_test_argomes.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_test_argomes.dir/build.make CMakeFiles/game_test_argomes.dir/game_test_argomes.c.i
.PHONY : game_test_argomes.c.i

game_test_argomes.s: game_test_argomes.c.s

.PHONY : game_test_argomes.s

# target to generate assembly for a file
game_test_argomes.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_test_argomes.dir/build.make CMakeFiles/game_test_argomes.dir/game_test_argomes.c.s
.PHONY : game_test_argomes.c.s

game_test_juruch.o: game_test_juruch.c.o

.PHONY : game_test_juruch.o

# target to build an object file
game_test_juruch.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_test_juruch.dir/build.make CMakeFiles/game_test_juruch.dir/game_test_juruch.c.o
.PHONY : game_test_juruch.c.o

game_test_juruch.i: game_test_juruch.c.i

.PHONY : game_test_juruch.i

# target to preprocess a source file
game_test_juruch.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_test_juruch.dir/build.make CMakeFiles/game_test_juruch.dir/game_test_juruch.c.i
.PHONY : game_test_juruch.c.i

game_test_juruch.s: game_test_juruch.c.s

.PHONY : game_test_juruch.s

# target to generate assembly for a file
game_test_juruch.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_test_juruch.dir/build.make CMakeFiles/game_test_juruch.dir/game_test_juruch.c.s
.PHONY : game_test_juruch.c.s

game_test_ymaabout.o: game_test_ymaabout.c.o

.PHONY : game_test_ymaabout.o

# target to build an object file
game_test_ymaabout.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_test_ymaabout.dir/build.make CMakeFiles/game_test_ymaabout.dir/game_test_ymaabout.c.o
.PHONY : game_test_ymaabout.c.o

game_test_ymaabout.i: game_test_ymaabout.c.i

.PHONY : game_test_ymaabout.i

# target to preprocess a source file
game_test_ymaabout.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_test_ymaabout.dir/build.make CMakeFiles/game_test_ymaabout.dir/game_test_ymaabout.c.i
.PHONY : game_test_ymaabout.c.i

game_test_ymaabout.s: game_test_ymaabout.c.s

.PHONY : game_test_ymaabout.s

# target to generate assembly for a file
game_test_ymaabout.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_test_ymaabout.dir/build.make CMakeFiles/game_test_ymaabout.dir/game_test_ymaabout.c.s
.PHONY : game_test_ymaabout.c.s

game_text.o: game_text.c.o

.PHONY : game_text.o

# target to build an object file
game_text.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_text.dir/build.make CMakeFiles/game_text.dir/game_text.c.o
.PHONY : game_text.c.o

game_text.i: game_text.c.i

.PHONY : game_text.i

# target to preprocess a source file
game_text.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_text.dir/build.make CMakeFiles/game_text.dir/game_text.c.i
.PHONY : game_text.c.i

game_text.s: game_text.c.s

.PHONY : game_text.s

# target to generate assembly for a file
game_text.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game_text.dir/build.make CMakeFiles/game_text.dir/game_text.c.s
.PHONY : game_text.c.s

queue.o: queue.c.o

.PHONY : queue.o

# target to build an object file
queue.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/queue.c.o
.PHONY : queue.c.o

queue.i: queue.c.i

.PHONY : queue.i

# target to preprocess a source file
queue.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/queue.c.i
.PHONY : queue.c.i

queue.s: queue.c.s

.PHONY : queue.s

# target to generate assembly for a file
queue.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/queue.c.s
.PHONY : queue.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... test"
	@echo "... Continuous"
	@echo "... ContinuousBuild"
	@echo "... ContinuousConfigure"
	@echo "... ContinuousCoverage"
	@echo "... ContinuousMemCheck"
	@echo "... ContinuousStart"
	@echo "... ContinuousSubmit"
	@echo "... ContinuousTest"
	@echo "... ContinuousUpdate"
	@echo "... Experimental"
	@echo "... ExperimentalBuild"
	@echo "... ExperimentalConfigure"
	@echo "... ExperimentalCoverage"
	@echo "... ExperimentalMemCheck"
	@echo "... ExperimentalStart"
	@echo "... ExperimentalSubmit"
	@echo "... ExperimentalTest"
	@echo "... ExperimentalUpdate"
	@echo "... Nightly"
	@echo "... NightlyBuild"
	@echo "... NightlyConfigure"
	@echo "... NightlyCoverage"
	@echo "... NightlyMemCheck"
	@echo "... NightlyMemoryCheck"
	@echo "... NightlyStart"
	@echo "... NightlySubmit"
	@echo "... NightlyTest"
	@echo "... NightlyUpdate"
	@echo "... game"
	@echo "... game_test_argomes"
	@echo "... game_test_juruch"
	@echo "... game_test_ymaabout"
	@echo "... game_text"
	@echo "... game.o"
	@echo "... game.i"
	@echo "... game.s"
	@echo "... game_aux.o"
	@echo "... game_aux.i"
	@echo "... game_aux.s"
	@echo "... game_ext.o"
	@echo "... game_ext.i"
	@echo "... game_ext.s"
	@echo "... game_test_argomes.o"
	@echo "... game_test_argomes.i"
	@echo "... game_test_argomes.s"
	@echo "... game_test_juruch.o"
	@echo "... game_test_juruch.i"
	@echo "... game_test_juruch.s"
	@echo "... game_test_ymaabout.o"
	@echo "... game_test_ymaabout.i"
	@echo "... game_test_ymaabout.s"
	@echo "... game_text.o"
	@echo "... game_text.i"
	@echo "... game_text.s"
	@echo "... queue.o"
	@echo "... queue.i"
	@echo "... queue.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

