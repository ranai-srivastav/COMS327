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
CMAKE_SOURCE_DIR = /home/ranai/Ranai/Fall22/COMS327/FaceSwap

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ranai/Ranai/Fall22/COMS327/FaceSwap/build

# Include any dependencies generated for this target.
include CMakeFiles/FaceSwap.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/FaceSwap.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/FaceSwap.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FaceSwap.dir/flags.make

CMakeFiles/FaceSwap.dir/main.cpp.o: CMakeFiles/FaceSwap.dir/flags.make
CMakeFiles/FaceSwap.dir/main.cpp.o: ../main.cpp
CMakeFiles/FaceSwap.dir/main.cpp.o: CMakeFiles/FaceSwap.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ranai/Ranai/Fall22/COMS327/FaceSwap/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FaceSwap.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FaceSwap.dir/main.cpp.o -MF CMakeFiles/FaceSwap.dir/main.cpp.o.d -o CMakeFiles/FaceSwap.dir/main.cpp.o -c /home/ranai/Ranai/Fall22/COMS327/FaceSwap/main.cpp

CMakeFiles/FaceSwap.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FaceSwap.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ranai/Ranai/Fall22/COMS327/FaceSwap/main.cpp > CMakeFiles/FaceSwap.dir/main.cpp.i

CMakeFiles/FaceSwap.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FaceSwap.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ranai/Ranai/Fall22/COMS327/FaceSwap/main.cpp -o CMakeFiles/FaceSwap.dir/main.cpp.s

# Object files for target FaceSwap
FaceSwap_OBJECTS = \
"CMakeFiles/FaceSwap.dir/main.cpp.o"

# External object files for target FaceSwap
FaceSwap_EXTERNAL_OBJECTS =

FaceSwap: CMakeFiles/FaceSwap.dir/main.cpp.o
FaceSwap: CMakeFiles/FaceSwap.dir/build.make
FaceSwap: /usr/local/lib/libopencv_gapi.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_highgui.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_ml.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_objdetect.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_photo.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_stitching.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_video.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_videoio.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_imgcodecs.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_dnn.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_calib3d.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_features2d.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_flann.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_imgproc.so.4.6.0
FaceSwap: /usr/local/lib/libopencv_core.so.4.6.0
FaceSwap: CMakeFiles/FaceSwap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ranai/Ranai/Fall22/COMS327/FaceSwap/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable FaceSwap"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FaceSwap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FaceSwap.dir/build: FaceSwap
.PHONY : CMakeFiles/FaceSwap.dir/build

CMakeFiles/FaceSwap.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FaceSwap.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FaceSwap.dir/clean

CMakeFiles/FaceSwap.dir/depend:
	cd /home/ranai/Ranai/Fall22/COMS327/FaceSwap/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ranai/Ranai/Fall22/COMS327/FaceSwap /home/ranai/Ranai/Fall22/COMS327/FaceSwap /home/ranai/Ranai/Fall22/COMS327/FaceSwap/build /home/ranai/Ranai/Fall22/COMS327/FaceSwap/build /home/ranai/Ranai/Fall22/COMS327/FaceSwap/build/CMakeFiles/FaceSwap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FaceSwap.dir/depend

