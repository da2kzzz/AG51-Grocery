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
CMAKE_SOURCE_DIR = D:\freeglut-3.0.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\freeglut-3.0.0\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/subwin.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/subwin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/subwin.dir/flags.make

CMakeFiles/subwin.dir/progs/demos/subwin/subwin.c.obj: CMakeFiles/subwin.dir/flags.make
CMakeFiles/subwin.dir/progs/demos/subwin/subwin.c.obj: CMakeFiles/subwin.dir/includes_C.rsp
CMakeFiles/subwin.dir/progs/demos/subwin/subwin.c.obj: ../progs/demos/subwin/subwin.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\freeglut-3.0.0\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/subwin.dir/progs/demos/subwin/subwin.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\subwin.dir\progs\demos\subwin\subwin.c.obj   -c D:\freeglut-3.0.0\progs\demos\subwin\subwin.c

CMakeFiles/subwin.dir/progs/demos/subwin/subwin.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/subwin.dir/progs/demos/subwin/subwin.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\freeglut-3.0.0\progs\demos\subwin\subwin.c > CMakeFiles\subwin.dir\progs\demos\subwin\subwin.c.i

CMakeFiles/subwin.dir/progs/demos/subwin/subwin.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/subwin.dir/progs/demos/subwin/subwin.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\freeglut-3.0.0\progs\demos\subwin\subwin.c -o CMakeFiles\subwin.dir\progs\demos\subwin\subwin.c.s

# Object files for target subwin
subwin_OBJECTS = \
"CMakeFiles/subwin.dir/progs/demos/subwin/subwin.c.obj"

# External object files for target subwin
subwin_EXTERNAL_OBJECTS =

bin/subwin.exe: CMakeFiles/subwin.dir/progs/demos/subwin/subwin.c.obj
bin/subwin.exe: CMakeFiles/subwin.dir/build.make
bin/subwin.exe: lib/libfreeglut.dll.a
bin/subwin.exe: CMakeFiles/subwin.dir/linklibs.rsp
bin/subwin.exe: CMakeFiles/subwin.dir/objects1.rsp
bin/subwin.exe: CMakeFiles/subwin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\freeglut-3.0.0\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin\subwin.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\subwin.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/subwin.dir/build: bin/subwin.exe

.PHONY : CMakeFiles/subwin.dir/build

CMakeFiles/subwin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\subwin.dir\cmake_clean.cmake
.PHONY : CMakeFiles/subwin.dir/clean

CMakeFiles/subwin.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\freeglut-3.0.0 D:\freeglut-3.0.0 D:\freeglut-3.0.0\cmake-build-debug D:\freeglut-3.0.0\cmake-build-debug D:\freeglut-3.0.0\cmake-build-debug\CMakeFiles\subwin.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/subwin.dir/depend

