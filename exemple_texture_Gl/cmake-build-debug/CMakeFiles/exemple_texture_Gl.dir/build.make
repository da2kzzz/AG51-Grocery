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
CMAKE_COMMAND = "D:\Programs\Clion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Programs\Clion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\C++\exemple_texture_Gl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\C++\exemple_texture_Gl\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/exemple_texture_Gl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/exemple_texture_Gl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exemple_texture_Gl.dir/flags.make

CMakeFiles/exemple_texture_Gl.dir/main.cpp.obj: CMakeFiles/exemple_texture_Gl.dir/flags.make
CMakeFiles/exemple_texture_Gl.dir/main.cpp.obj: CMakeFiles/exemple_texture_Gl.dir/includes_CXX.rsp
CMakeFiles/exemple_texture_Gl.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\C++\exemple_texture_Gl\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exemple_texture_Gl.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\exemple_texture_Gl.dir\main.cpp.obj -c D:\C++\exemple_texture_Gl\main.cpp

CMakeFiles/exemple_texture_Gl.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exemple_texture_Gl.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\C++\exemple_texture_Gl\main.cpp > CMakeFiles\exemple_texture_Gl.dir\main.cpp.i

CMakeFiles/exemple_texture_Gl.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exemple_texture_Gl.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\C++\exemple_texture_Gl\main.cpp -o CMakeFiles\exemple_texture_Gl.dir\main.cpp.s

# Object files for target exemple_texture_Gl
exemple_texture_Gl_OBJECTS = \
"CMakeFiles/exemple_texture_Gl.dir/main.cpp.obj"

# External object files for target exemple_texture_Gl
exemple_texture_Gl_EXTERNAL_OBJECTS =

exemple_texture_Gl.exe: CMakeFiles/exemple_texture_Gl.dir/main.cpp.obj
exemple_texture_Gl.exe: CMakeFiles/exemple_texture_Gl.dir/build.make
exemple_texture_Gl.exe: CMakeFiles/exemple_texture_Gl.dir/linklibs.rsp
exemple_texture_Gl.exe: CMakeFiles/exemple_texture_Gl.dir/objects1.rsp
exemple_texture_Gl.exe: CMakeFiles/exemple_texture_Gl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\C++\exemple_texture_Gl\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable exemple_texture_Gl.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\exemple_texture_Gl.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exemple_texture_Gl.dir/build: exemple_texture_Gl.exe

.PHONY : CMakeFiles/exemple_texture_Gl.dir/build

CMakeFiles/exemple_texture_Gl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\exemple_texture_Gl.dir\cmake_clean.cmake
.PHONY : CMakeFiles/exemple_texture_Gl.dir/clean

CMakeFiles/exemple_texture_Gl.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\C++\exemple_texture_Gl D:\C++\exemple_texture_Gl D:\C++\exemple_texture_Gl\cmake-build-debug D:\C++\exemple_texture_Gl\cmake-build-debug D:\C++\exemple_texture_Gl\cmake-build-debug\CMakeFiles\exemple_texture_Gl.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exemple_texture_Gl.dir/depend

