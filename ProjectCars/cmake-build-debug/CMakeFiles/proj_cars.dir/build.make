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
CMAKE_SOURCE_DIR = D:\C++\ProjectCars

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\C++\ProjectCars\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/proj_cars.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/proj_cars.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/proj_cars.dir/flags.make

CMakeFiles/proj_cars.dir/main.cpp.obj: CMakeFiles/proj_cars.dir/flags.make
CMakeFiles/proj_cars.dir/main.cpp.obj: CMakeFiles/proj_cars.dir/includes_CXX.rsp
CMakeFiles/proj_cars.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\C++\ProjectCars\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/proj_cars.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\proj_cars.dir\main.cpp.obj -c D:\C++\ProjectCars\main.cpp

CMakeFiles/proj_cars.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proj_cars.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\C++\ProjectCars\main.cpp > CMakeFiles\proj_cars.dir\main.cpp.i

CMakeFiles/proj_cars.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proj_cars.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\C++\ProjectCars\main.cpp -o CMakeFiles\proj_cars.dir\main.cpp.s

CMakeFiles/proj_cars.dir/Mesh.cpp.obj: CMakeFiles/proj_cars.dir/flags.make
CMakeFiles/proj_cars.dir/Mesh.cpp.obj: CMakeFiles/proj_cars.dir/includes_CXX.rsp
CMakeFiles/proj_cars.dir/Mesh.cpp.obj: ../Mesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\C++\ProjectCars\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/proj_cars.dir/Mesh.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\proj_cars.dir\Mesh.cpp.obj -c D:\C++\ProjectCars\Mesh.cpp

CMakeFiles/proj_cars.dir/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proj_cars.dir/Mesh.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\C++\ProjectCars\Mesh.cpp > CMakeFiles\proj_cars.dir\Mesh.cpp.i

CMakeFiles/proj_cars.dir/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proj_cars.dir/Mesh.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\C++\ProjectCars\Mesh.cpp -o CMakeFiles\proj_cars.dir\Mesh.cpp.s

CMakeFiles/proj_cars.dir/Voronoi.cpp.obj: CMakeFiles/proj_cars.dir/flags.make
CMakeFiles/proj_cars.dir/Voronoi.cpp.obj: CMakeFiles/proj_cars.dir/includes_CXX.rsp
CMakeFiles/proj_cars.dir/Voronoi.cpp.obj: ../Voronoi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\C++\ProjectCars\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/proj_cars.dir/Voronoi.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\proj_cars.dir\Voronoi.cpp.obj -c D:\C++\ProjectCars\Voronoi.cpp

CMakeFiles/proj_cars.dir/Voronoi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proj_cars.dir/Voronoi.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\C++\ProjectCars\Voronoi.cpp > CMakeFiles\proj_cars.dir\Voronoi.cpp.i

CMakeFiles/proj_cars.dir/Voronoi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proj_cars.dir/Voronoi.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\C++\ProjectCars\Voronoi.cpp -o CMakeFiles\proj_cars.dir\Voronoi.cpp.s

CMakeFiles/proj_cars.dir/Polygon.cpp.obj: CMakeFiles/proj_cars.dir/flags.make
CMakeFiles/proj_cars.dir/Polygon.cpp.obj: CMakeFiles/proj_cars.dir/includes_CXX.rsp
CMakeFiles/proj_cars.dir/Polygon.cpp.obj: ../Polygon.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\C++\ProjectCars\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/proj_cars.dir/Polygon.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\proj_cars.dir\Polygon.cpp.obj -c D:\C++\ProjectCars\Polygon.cpp

CMakeFiles/proj_cars.dir/Polygon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proj_cars.dir/Polygon.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\C++\ProjectCars\Polygon.cpp > CMakeFiles\proj_cars.dir\Polygon.cpp.i

CMakeFiles/proj_cars.dir/Polygon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proj_cars.dir/Polygon.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\C++\ProjectCars\Polygon.cpp -o CMakeFiles\proj_cars.dir\Polygon.cpp.s

CMakeFiles/proj_cars.dir/Cars.cpp.obj: CMakeFiles/proj_cars.dir/flags.make
CMakeFiles/proj_cars.dir/Cars.cpp.obj: CMakeFiles/proj_cars.dir/includes_CXX.rsp
CMakeFiles/proj_cars.dir/Cars.cpp.obj: ../Cars.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\C++\ProjectCars\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/proj_cars.dir/Cars.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\proj_cars.dir\Cars.cpp.obj -c D:\C++\ProjectCars\Cars.cpp

CMakeFiles/proj_cars.dir/Cars.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proj_cars.dir/Cars.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\C++\ProjectCars\Cars.cpp > CMakeFiles\proj_cars.dir\Cars.cpp.i

CMakeFiles/proj_cars.dir/Cars.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proj_cars.dir/Cars.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\C++\ProjectCars\Cars.cpp -o CMakeFiles\proj_cars.dir\Cars.cpp.s

CMakeFiles/proj_cars.dir/Vector2D.cpp.obj: CMakeFiles/proj_cars.dir/flags.make
CMakeFiles/proj_cars.dir/Vector2D.cpp.obj: CMakeFiles/proj_cars.dir/includes_CXX.rsp
CMakeFiles/proj_cars.dir/Vector2D.cpp.obj: ../Vector2D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\C++\ProjectCars\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/proj_cars.dir/Vector2D.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\proj_cars.dir\Vector2D.cpp.obj -c D:\C++\ProjectCars\Vector2D.cpp

CMakeFiles/proj_cars.dir/Vector2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proj_cars.dir/Vector2D.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\C++\ProjectCars\Vector2D.cpp > CMakeFiles\proj_cars.dir\Vector2D.cpp.i

CMakeFiles/proj_cars.dir/Vector2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proj_cars.dir/Vector2D.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\C++\ProjectCars\Vector2D.cpp -o CMakeFiles\proj_cars.dir\Vector2D.cpp.s

CMakeFiles/proj_cars.dir/determinant.cpp.obj: CMakeFiles/proj_cars.dir/flags.make
CMakeFiles/proj_cars.dir/determinant.cpp.obj: CMakeFiles/proj_cars.dir/includes_CXX.rsp
CMakeFiles/proj_cars.dir/determinant.cpp.obj: ../determinant.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\C++\ProjectCars\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/proj_cars.dir/determinant.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\proj_cars.dir\determinant.cpp.obj -c D:\C++\ProjectCars\determinant.cpp

CMakeFiles/proj_cars.dir/determinant.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proj_cars.dir/determinant.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\C++\ProjectCars\determinant.cpp > CMakeFiles\proj_cars.dir\determinant.cpp.i

CMakeFiles/proj_cars.dir/determinant.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proj_cars.dir/determinant.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\C++\ProjectCars\determinant.cpp -o CMakeFiles\proj_cars.dir\determinant.cpp.s

# Object files for target proj_cars
proj_cars_OBJECTS = \
"CMakeFiles/proj_cars.dir/main.cpp.obj" \
"CMakeFiles/proj_cars.dir/Mesh.cpp.obj" \
"CMakeFiles/proj_cars.dir/Voronoi.cpp.obj" \
"CMakeFiles/proj_cars.dir/Polygon.cpp.obj" \
"CMakeFiles/proj_cars.dir/Cars.cpp.obj" \
"CMakeFiles/proj_cars.dir/Vector2D.cpp.obj" \
"CMakeFiles/proj_cars.dir/determinant.cpp.obj"

# External object files for target proj_cars
proj_cars_EXTERNAL_OBJECTS =

proj_cars.exe: CMakeFiles/proj_cars.dir/main.cpp.obj
proj_cars.exe: CMakeFiles/proj_cars.dir/Mesh.cpp.obj
proj_cars.exe: CMakeFiles/proj_cars.dir/Voronoi.cpp.obj
proj_cars.exe: CMakeFiles/proj_cars.dir/Polygon.cpp.obj
proj_cars.exe: CMakeFiles/proj_cars.dir/Cars.cpp.obj
proj_cars.exe: CMakeFiles/proj_cars.dir/Vector2D.cpp.obj
proj_cars.exe: CMakeFiles/proj_cars.dir/determinant.cpp.obj
proj_cars.exe: CMakeFiles/proj_cars.dir/build.make
proj_cars.exe: CMakeFiles/proj_cars.dir/linklibs.rsp
proj_cars.exe: CMakeFiles/proj_cars.dir/objects1.rsp
proj_cars.exe: CMakeFiles/proj_cars.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\C++\ProjectCars\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable proj_cars.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\proj_cars.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/proj_cars.dir/build: proj_cars.exe

.PHONY : CMakeFiles/proj_cars.dir/build

CMakeFiles/proj_cars.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\proj_cars.dir\cmake_clean.cmake
.PHONY : CMakeFiles/proj_cars.dir/clean

CMakeFiles/proj_cars.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\C++\ProjectCars D:\C++\ProjectCars D:\C++\ProjectCars\cmake-build-debug D:\C++\ProjectCars\cmake-build-debug D:\C++\ProjectCars\cmake-build-debug\CMakeFiles\proj_cars.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/proj_cars.dir/depend

