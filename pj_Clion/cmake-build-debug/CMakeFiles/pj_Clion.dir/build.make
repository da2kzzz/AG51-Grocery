# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\clion\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\clion\CLion 2020.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\C++\pj_Clion

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\C++\pj_Clion\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/pj_Clion.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pj_Clion.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pj_Clion.dir/flags.make

CMakeFiles/pj_Clion.dir/main.cpp.obj: CMakeFiles/pj_Clion.dir/flags.make
CMakeFiles/pj_Clion.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\C++\pj_Clion\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pj_Clion.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\pj_Clion.dir\main.cpp.obj -c D:\C++\pj_Clion\main.cpp

CMakeFiles/pj_Clion.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pj_Clion.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\C++\pj_Clion\main.cpp > CMakeFiles\pj_Clion.dir\main.cpp.i

CMakeFiles/pj_Clion.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pj_Clion.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\C++\pj_Clion\main.cpp -o CMakeFiles\pj_Clion.dir\main.cpp.s

# Object files for target pj_Clion
pj_Clion_OBJECTS = \
"CMakeFiles/pj_Clion.dir/main.cpp.obj"

# External object files for target pj_Clion
pj_Clion_EXTERNAL_OBJECTS =

pj_Clion.exe: CMakeFiles/pj_Clion.dir/main.cpp.obj
pj_Clion.exe: CMakeFiles/pj_Clion.dir/build.make
pj_Clion.exe: CMakeFiles/pj_Clion.dir/linklibs.rsp
pj_Clion.exe: CMakeFiles/pj_Clion.dir/objects1.rsp
pj_Clion.exe: CMakeFiles/pj_Clion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\C++\pj_Clion\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pj_Clion.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\pj_Clion.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pj_Clion.dir/build: pj_Clion.exe

.PHONY : CMakeFiles/pj_Clion.dir/build

CMakeFiles/pj_Clion.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\pj_Clion.dir\cmake_clean.cmake
.PHONY : CMakeFiles/pj_Clion.dir/clean

CMakeFiles/pj_Clion.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\C++\pj_Clion D:\C++\pj_Clion D:\C++\pj_Clion\cmake-build-debug D:\C++\pj_Clion\cmake-build-debug D:\C++\pj_Clion\cmake-build-debug\CMakeFiles\pj_Clion.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pj_Clion.dir/depend

