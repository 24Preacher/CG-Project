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
CMAKE_COMMAND = /home/addams/Downloads/CLion-2019.3.5/clion-2019.3.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/addams/Downloads/CLion-2019.3.5/clion-2019.3.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/addams/Desktop/Universidade/CG/ficha6/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/addams/Desktop/Universidade/CG/ficha6/code/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/class6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/class6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/class6.dir/flags.make

CMakeFiles/class6.dir/main.cpp.o: CMakeFiles/class6.dir/flags.make
CMakeFiles/class6.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/addams/Desktop/Universidade/CG/ficha6/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/class6.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/class6.dir/main.cpp.o -c /home/addams/Desktop/Universidade/CG/ficha6/code/main.cpp

CMakeFiles/class6.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/class6.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/addams/Desktop/Universidade/CG/ficha6/code/main.cpp > CMakeFiles/class6.dir/main.cpp.i

CMakeFiles/class6.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/class6.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/addams/Desktop/Universidade/CG/ficha6/code/main.cpp -o CMakeFiles/class6.dir/main.cpp.s

# Object files for target class6
class6_OBJECTS = \
"CMakeFiles/class6.dir/main.cpp.o"

# External object files for target class6
class6_EXTERNAL_OBJECTS =

class6: CMakeFiles/class6.dir/main.cpp.o
class6: CMakeFiles/class6.dir/build.make
class6: /usr/lib/x86_64-linux-gnu/libGL.so
class6: /usr/lib/x86_64-linux-gnu/libGLU.so
class6: /usr/lib/x86_64-linux-gnu/libglut.so
class6: /usr/lib/x86_64-linux-gnu/libXmu.so
class6: /usr/lib/x86_64-linux-gnu/libXi.so
class6: /usr/lib/x86_64-linux-gnu/libIL.so
class6: CMakeFiles/class6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/addams/Desktop/Universidade/CG/ficha6/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable class6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/class6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/class6.dir/build: class6

.PHONY : CMakeFiles/class6.dir/build

CMakeFiles/class6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/class6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/class6.dir/clean

CMakeFiles/class6.dir/depend:
	cd /home/addams/Desktop/Universidade/CG/ficha6/code/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/addams/Desktop/Universidade/CG/ficha6/code /home/addams/Desktop/Universidade/CG/ficha6/code /home/addams/Desktop/Universidade/CG/ficha6/code/cmake-build-debug /home/addams/Desktop/Universidade/CG/ficha6/code/cmake-build-debug /home/addams/Desktop/Universidade/CG/ficha6/code/cmake-build-debug/CMakeFiles/class6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/class6.dir/depend

