# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/Desktop/test/rpicomponents

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Desktop/test/rpicomponents

# Include any dependencies generated for this target.
include test/CMakeFiles/test_project.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_project.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_project.dir/flags.make

test/CMakeFiles/test_project.dir/src/test.cpp.o: test/CMakeFiles/test_project.dir/flags.make
test/CMakeFiles/test_project.dir/src/test.cpp.o: test/src/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Desktop/test/rpicomponents/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test_project.dir/src/test.cpp.o"
	cd /home/pi/Desktop/test/rpicomponents/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_project.dir/src/test.cpp.o -c /home/pi/Desktop/test/rpicomponents/test/src/test.cpp

test/CMakeFiles/test_project.dir/src/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_project.dir/src/test.cpp.i"
	cd /home/pi/Desktop/test/rpicomponents/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Desktop/test/rpicomponents/test/src/test.cpp > CMakeFiles/test_project.dir/src/test.cpp.i

test/CMakeFiles/test_project.dir/src/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_project.dir/src/test.cpp.s"
	cd /home/pi/Desktop/test/rpicomponents/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Desktop/test/rpicomponents/test/src/test.cpp -o CMakeFiles/test_project.dir/src/test.cpp.s

test/CMakeFiles/test_project.dir/src/test.cpp.o.requires:

.PHONY : test/CMakeFiles/test_project.dir/src/test.cpp.o.requires

test/CMakeFiles/test_project.dir/src/test.cpp.o.provides: test/CMakeFiles/test_project.dir/src/test.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/test_project.dir/build.make test/CMakeFiles/test_project.dir/src/test.cpp.o.provides.build
.PHONY : test/CMakeFiles/test_project.dir/src/test.cpp.o.provides

test/CMakeFiles/test_project.dir/src/test.cpp.o.provides.build: test/CMakeFiles/test_project.dir/src/test.cpp.o


# Object files for target test_project
test_project_OBJECTS = \
"CMakeFiles/test_project.dir/src/test.cpp.o"

# External object files for target test_project
test_project_EXTERNAL_OBJECTS =

build/test_project: test/CMakeFiles/test_project.dir/src/test.cpp.o
build/test_project: test/CMakeFiles/test_project.dir/build.make
build/test_project: build/libRPiComponents.so
build/test_project: build/libpin.so
build/test_project: build/librpicomponents_utils.so
build/test_project: test/CMakeFiles/test_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Desktop/test/rpicomponents/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../build/test_project"
	cd /home/pi/Desktop/test/rpicomponents/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_project.dir/build: build/test_project

.PHONY : test/CMakeFiles/test_project.dir/build

test/CMakeFiles/test_project.dir/requires: test/CMakeFiles/test_project.dir/src/test.cpp.o.requires

.PHONY : test/CMakeFiles/test_project.dir/requires

test/CMakeFiles/test_project.dir/clean:
	cd /home/pi/Desktop/test/rpicomponents/test && $(CMAKE_COMMAND) -P CMakeFiles/test_project.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_project.dir/clean

test/CMakeFiles/test_project.dir/depend:
	cd /home/pi/Desktop/test/rpicomponents && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Desktop/test/rpicomponents /home/pi/Desktop/test/rpicomponents/test /home/pi/Desktop/test/rpicomponents /home/pi/Desktop/test/rpicomponents/test /home/pi/Desktop/test/rpicomponents/test/CMakeFiles/test_project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_project.dir/depend

