# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache/build"

# Include any dependencies generated for this target.
include CMakeFiles/cache.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cache.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cache.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cache.dir/flags.make

CMakeFiles/cache.dir/Source/cache.cpp.o: CMakeFiles/cache.dir/flags.make
CMakeFiles/cache.dir/Source/cache.cpp.o: ../Source/cache.cpp
CMakeFiles/cache.dir/Source/cache.cpp.o: CMakeFiles/cache.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cache.dir/Source/cache.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cache.dir/Source/cache.cpp.o -MF CMakeFiles/cache.dir/Source/cache.cpp.o.d -o CMakeFiles/cache.dir/Source/cache.cpp.o -c "/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache/Source/cache.cpp"

CMakeFiles/cache.dir/Source/cache.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cache.dir/Source/cache.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache/Source/cache.cpp" > CMakeFiles/cache.dir/Source/cache.cpp.i

CMakeFiles/cache.dir/Source/cache.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cache.dir/Source/cache.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache/Source/cache.cpp" -o CMakeFiles/cache.dir/Source/cache.cpp.s

# Object files for target cache
cache_OBJECTS = \
"CMakeFiles/cache.dir/Source/cache.cpp.o"

# External object files for target cache
cache_EXTERNAL_OBJECTS =

cache: CMakeFiles/cache.dir/Source/cache.cpp.o
cache: CMakeFiles/cache.dir/build.make
cache: CMakeFiles/cache.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cache"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cache.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cache.dir/build: cache
.PHONY : CMakeFiles/cache.dir/build

CMakeFiles/cache.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cache.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cache.dir/clean

CMakeFiles/cache.dir/depend:
	cd "/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache" "/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache" "/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache/build" "/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache/build" "/home/vlad/Учёба/Программирование/3 semester/Cpp_course_23_24/01-HWC-LFU-cache/build/CMakeFiles/cache.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/cache.dir/depend
