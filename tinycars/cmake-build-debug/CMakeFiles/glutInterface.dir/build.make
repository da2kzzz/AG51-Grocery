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
CMAKE_SOURCE_DIR = D:\C++\tinycars

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\C++\tinycars\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/glutInterface.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/glutInterface.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glutInterface.dir/flags.make

CMakeFiles/glutInterface.dir/glutWindow.cpp.obj: CMakeFiles/glutInterface.dir/flags.make
CMakeFiles/glutInterface.dir/glutWindow.cpp.obj: CMakeFiles/glutInterface.dir/includes_CXX.rsp
CMakeFiles/glutInterface.dir/glutWindow.cpp.obj: ../glutWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\C++\tinycars\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/glutInterface.dir/glutWindow.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\glutInterface.dir\glutWindow.cpp.obj -c D:\C++\tinycars\glutWindow.cpp

CMakeFiles/glutInterface.dir/glutWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glutInterface.dir/glutWindow.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\C++\tinycars\glutWindow.cpp > CMakeFiles\glutInterface.dir\glutWindow.cpp.i

CMakeFiles/glutInterface.dir/glutWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glutInterface.dir/glutWindow.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\C++\tinycars\glutWindow.cpp -o CMakeFiles\glutInterface.dir\glutWindow.cpp.s

# Object files for target glutInterface
glutInterface_OBJECTS = \
"CMakeFiles/glutInterface.dir/glutWindow.cpp.obj"

# External object files for target glutInterface
glutInterface_EXTERNAL_OBJECTS =

libglutInterface.a: CMakeFiles/glutInterface.dir/glutWindow.cpp.obj
libglutInterface.a: CMakeFiles/glutInterface.dir/build.make
libglutInterface.a: CMakeFiles/glutInterface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\C++\tinycars\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libglutInterface.a"
	$(CMAKE_COMMAND) -P CMakeFiles\glutInterface.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\glutInterface.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glutInterface.dir/build: libglutInterface.a

.PHONY : CMakeFiles/glutInterface.dir/build

CMakeFiles/glutInterface.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\glutInterface.dir\cmake_clean.cmake
.PHONY : CMakeFiles/glutInterface.dir/clean

CMakeFiles/glutInterface.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\C++\tinycars D:\C++\tinycars D:\C++\tinycars\cmake-build-debug D:\C++\tinycars\cmake-build-debug D:\C++\tinycars\cmake-build-debug\CMakeFiles\glutInterface.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glutInterface.dir/depend
