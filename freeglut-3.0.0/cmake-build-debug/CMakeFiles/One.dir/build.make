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
include CMakeFiles/One.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/One.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/One.dir/flags.make

CMakeFiles/One.dir/progs/demos/One/one.c.obj: CMakeFiles/One.dir/flags.make
CMakeFiles/One.dir/progs/demos/One/one.c.obj: CMakeFiles/One.dir/includes_C.rsp
CMakeFiles/One.dir/progs/demos/One/one.c.obj: ../progs/demos/One/one.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\freeglut-3.0.0\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/One.dir/progs/demos/One/one.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\One.dir\progs\demos\One\one.c.obj   -c D:\freeglut-3.0.0\progs\demos\One\one.c

CMakeFiles/One.dir/progs/demos/One/one.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/One.dir/progs/demos/One/one.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\freeglut-3.0.0\progs\demos\One\one.c > CMakeFiles\One.dir\progs\demos\One\one.c.i

CMakeFiles/One.dir/progs/demos/One/one.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/One.dir/progs/demos/One/one.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\freeglut-3.0.0\progs\demos\One\one.c -o CMakeFiles\One.dir\progs\demos\One\one.c.s

CMakeFiles/One.dir/progs/demos/One/one.rc.obj: CMakeFiles/One.dir/flags.make
CMakeFiles/One.dir/progs/demos/One/one.rc.obj: ../progs/demos/One/one.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\freeglut-3.0.0\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building RC object CMakeFiles/One.dir/progs/demos/One/one.rc.obj"
	C:\MinGW\bin\windres.exe -O coff $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) D:\freeglut-3.0.0\progs\demos\One\one.rc CMakeFiles\One.dir\progs\demos\One\one.rc.obj

# Object files for target One
One_OBJECTS = \
"CMakeFiles/One.dir/progs/demos/One/one.c.obj" \
"CMakeFiles/One.dir/progs/demos/One/one.rc.obj"

# External object files for target One
One_EXTERNAL_OBJECTS =

bin/One.exe: CMakeFiles/One.dir/progs/demos/One/one.c.obj
bin/One.exe: CMakeFiles/One.dir/progs/demos/One/one.rc.obj
bin/One.exe: CMakeFiles/One.dir/build.make
bin/One.exe: lib/libfreeglut.dll.a
bin/One.exe: CMakeFiles/One.dir/linklibs.rsp
bin/One.exe: CMakeFiles/One.dir/objects1.rsp
bin/One.exe: CMakeFiles/One.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\freeglut-3.0.0\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable bin\One.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\One.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/One.dir/build: bin/One.exe

.PHONY : CMakeFiles/One.dir/build

CMakeFiles/One.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\One.dir\cmake_clean.cmake
.PHONY : CMakeFiles/One.dir/clean

CMakeFiles/One.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\freeglut-3.0.0 D:\freeglut-3.0.0 D:\freeglut-3.0.0\cmake-build-debug D:\freeglut-3.0.0\cmake-build-debug D:\freeglut-3.0.0\cmake-build-debug\CMakeFiles\One.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/One.dir/depend

