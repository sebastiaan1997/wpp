# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/sebas/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.5662.56/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/sebas/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.5662.56/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sebas/projects/cxx/wpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sebas/projects/cxx/wpp/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/wpp_demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wpp_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wpp_demo.dir/flags.make

CMakeFiles/wpp_demo.dir/demo.cpp.o: CMakeFiles/wpp_demo.dir/flags.make
CMakeFiles/wpp_demo.dir/demo.cpp.o: ../demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sebas/projects/cxx/wpp/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wpp_demo.dir/demo.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wpp_demo.dir/demo.cpp.o -c /home/sebas/projects/cxx/wpp/demo.cpp

CMakeFiles/wpp_demo.dir/demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wpp_demo.dir/demo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sebas/projects/cxx/wpp/demo.cpp > CMakeFiles/wpp_demo.dir/demo.cpp.i

CMakeFiles/wpp_demo.dir/demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wpp_demo.dir/demo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sebas/projects/cxx/wpp/demo.cpp -o CMakeFiles/wpp_demo.dir/demo.cpp.s

# Object files for target wpp_demo
wpp_demo_OBJECTS = \
"CMakeFiles/wpp_demo.dir/demo.cpp.o"

# External object files for target wpp_demo
wpp_demo_EXTERNAL_OBJECTS =

wpp_demo: CMakeFiles/wpp_demo.dir/demo.cpp.o
wpp_demo: CMakeFiles/wpp_demo.dir/build.make
wpp_demo: libwpp.a
wpp_demo: CMakeFiles/wpp_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sebas/projects/cxx/wpp/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable wpp_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wpp_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wpp_demo.dir/build: wpp_demo

.PHONY : CMakeFiles/wpp_demo.dir/build

CMakeFiles/wpp_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wpp_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wpp_demo.dir/clean

CMakeFiles/wpp_demo.dir/depend:
	cd /home/sebas/projects/cxx/wpp/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sebas/projects/cxx/wpp /home/sebas/projects/cxx/wpp /home/sebas/projects/cxx/wpp/cmake-build-release /home/sebas/projects/cxx/wpp/cmake-build-release /home/sebas/projects/cxx/wpp/cmake-build-release/CMakeFiles/wpp_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wpp_demo.dir/depend

