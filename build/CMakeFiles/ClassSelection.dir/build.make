# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_COMMAND = /root/cmake/bin/cmake

# The command to remove a file.
RM = /root/cmake/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/ClassSelection

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/ClassSelection/build

# Include any dependencies generated for this target.
include CMakeFiles/ClassSelection.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ClassSelection.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ClassSelection.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ClassSelection.dir/flags.make

CMakeFiles/ClassSelection.dir/main.cpp.o: CMakeFiles/ClassSelection.dir/flags.make
CMakeFiles/ClassSelection.dir/main.cpp.o: ../main.cpp
CMakeFiles/ClassSelection.dir/main.cpp.o: CMakeFiles/ClassSelection.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/ClassSelection/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ClassSelection.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ClassSelection.dir/main.cpp.o -MF CMakeFiles/ClassSelection.dir/main.cpp.o.d -o CMakeFiles/ClassSelection.dir/main.cpp.o -c /root/ClassSelection/main.cpp

CMakeFiles/ClassSelection.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ClassSelection.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/ClassSelection/main.cpp > CMakeFiles/ClassSelection.dir/main.cpp.i

CMakeFiles/ClassSelection.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ClassSelection.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/ClassSelection/main.cpp -o CMakeFiles/ClassSelection.dir/main.cpp.s

# Object files for target ClassSelection
ClassSelection_OBJECTS = \
"CMakeFiles/ClassSelection.dir/main.cpp.o"

# External object files for target ClassSelection
ClassSelection_EXTERNAL_OBJECTS =

ClassSelection: CMakeFiles/ClassSelection.dir/main.cpp.o
ClassSelection: CMakeFiles/ClassSelection.dir/build.make
ClassSelection: libcore.a
ClassSelection: CMakeFiles/ClassSelection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/ClassSelection/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ClassSelection"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ClassSelection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ClassSelection.dir/build: ClassSelection
.PHONY : CMakeFiles/ClassSelection.dir/build

CMakeFiles/ClassSelection.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ClassSelection.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ClassSelection.dir/clean

CMakeFiles/ClassSelection.dir/depend:
	cd /root/ClassSelection/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ClassSelection /root/ClassSelection /root/ClassSelection/build /root/ClassSelection/build /root/ClassSelection/build/CMakeFiles/ClassSelection.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ClassSelection.dir/depend

