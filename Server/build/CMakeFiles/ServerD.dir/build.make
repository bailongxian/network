# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bailongxian/Blx/NetWorK/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bailongxian/Blx/NetWorK/Server/build

# Include any dependencies generated for this target.
include CMakeFiles/ServerD.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ServerD.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ServerD.dir/flags.make

CMakeFiles/ServerD.dir/Main.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/Main.cpp.o: ../Main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/Main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/Main.cpp.o -c /home/bailongxian/Blx/NetWorK/Server/Main.cpp

CMakeFiles/ServerD.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/Main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Server/Main.cpp > CMakeFiles/ServerD.dir/Main.cpp.i

CMakeFiles/ServerD.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/Main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Server/Main.cpp -o CMakeFiles/ServerD.dir/Main.cpp.s

CMakeFiles/ServerD.dir/Main.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/Main.cpp.o.requires

CMakeFiles/ServerD.dir/Main.cpp.o.provides: CMakeFiles/ServerD.dir/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/Main.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/Main.cpp.o.provides

CMakeFiles/ServerD.dir/Main.cpp.o.provides.build: CMakeFiles/ServerD.dir/Main.cpp.o

CMakeFiles/ServerD.dir/src/EventLoop.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/src/EventLoop.cpp.o: ../src/EventLoop.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/src/EventLoop.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/src/EventLoop.cpp.o -c /home/bailongxian/Blx/NetWorK/Server/src/EventLoop.cpp

CMakeFiles/ServerD.dir/src/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/src/EventLoop.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Server/src/EventLoop.cpp > CMakeFiles/ServerD.dir/src/EventLoop.cpp.i

CMakeFiles/ServerD.dir/src/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/src/EventLoop.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Server/src/EventLoop.cpp -o CMakeFiles/ServerD.dir/src/EventLoop.cpp.s

CMakeFiles/ServerD.dir/src/EventLoop.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/src/EventLoop.cpp.o.requires

CMakeFiles/ServerD.dir/src/EventLoop.cpp.o.provides: CMakeFiles/ServerD.dir/src/EventLoop.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/src/EventLoop.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/src/EventLoop.cpp.o.provides

CMakeFiles/ServerD.dir/src/EventLoop.cpp.o.provides.build: CMakeFiles/ServerD.dir/src/EventLoop.cpp.o

CMakeFiles/ServerD.dir/src/Message.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/src/Message.cpp.o: ../src/Message.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/src/Message.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/src/Message.cpp.o -c /home/bailongxian/Blx/NetWorK/Server/src/Message.cpp

CMakeFiles/ServerD.dir/src/Message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/src/Message.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Server/src/Message.cpp > CMakeFiles/ServerD.dir/src/Message.cpp.i

CMakeFiles/ServerD.dir/src/Message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/src/Message.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Server/src/Message.cpp -o CMakeFiles/ServerD.dir/src/Message.cpp.s

CMakeFiles/ServerD.dir/src/Message.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/src/Message.cpp.o.requires

CMakeFiles/ServerD.dir/src/Message.cpp.o.provides: CMakeFiles/ServerD.dir/src/Message.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/src/Message.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/src/Message.cpp.o.provides

CMakeFiles/ServerD.dir/src/Message.cpp.o.provides.build: CMakeFiles/ServerD.dir/src/Message.cpp.o

CMakeFiles/ServerD.dir/src/Connector.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/src/Connector.cpp.o: ../src/Connector.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/src/Connector.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/src/Connector.cpp.o -c /home/bailongxian/Blx/NetWorK/Server/src/Connector.cpp

CMakeFiles/ServerD.dir/src/Connector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/src/Connector.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Server/src/Connector.cpp > CMakeFiles/ServerD.dir/src/Connector.cpp.i

CMakeFiles/ServerD.dir/src/Connector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/src/Connector.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Server/src/Connector.cpp -o CMakeFiles/ServerD.dir/src/Connector.cpp.s

CMakeFiles/ServerD.dir/src/Connector.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/src/Connector.cpp.o.requires

CMakeFiles/ServerD.dir/src/Connector.cpp.o.provides: CMakeFiles/ServerD.dir/src/Connector.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/src/Connector.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/src/Connector.cpp.o.provides

CMakeFiles/ServerD.dir/src/Connector.cpp.o.provides.build: CMakeFiles/ServerD.dir/src/Connector.cpp.o

CMakeFiles/ServerD.dir/src/Common.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/src/Common.cpp.o: ../src/Common.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/src/Common.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/src/Common.cpp.o -c /home/bailongxian/Blx/NetWorK/Server/src/Common.cpp

CMakeFiles/ServerD.dir/src/Common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/src/Common.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Server/src/Common.cpp > CMakeFiles/ServerD.dir/src/Common.cpp.i

CMakeFiles/ServerD.dir/src/Common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/src/Common.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Server/src/Common.cpp -o CMakeFiles/ServerD.dir/src/Common.cpp.s

CMakeFiles/ServerD.dir/src/Common.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/src/Common.cpp.o.requires

CMakeFiles/ServerD.dir/src/Common.cpp.o.provides: CMakeFiles/ServerD.dir/src/Common.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/src/Common.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/src/Common.cpp.o.provides

CMakeFiles/ServerD.dir/src/Common.cpp.o.provides.build: CMakeFiles/ServerD.dir/src/Common.cpp.o

CMakeFiles/ServerD.dir/src/TimeList.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/src/TimeList.cpp.o: ../src/TimeList.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/src/TimeList.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/src/TimeList.cpp.o -c /home/bailongxian/Blx/NetWorK/Server/src/TimeList.cpp

CMakeFiles/ServerD.dir/src/TimeList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/src/TimeList.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Server/src/TimeList.cpp > CMakeFiles/ServerD.dir/src/TimeList.cpp.i

CMakeFiles/ServerD.dir/src/TimeList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/src/TimeList.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Server/src/TimeList.cpp -o CMakeFiles/ServerD.dir/src/TimeList.cpp.s

CMakeFiles/ServerD.dir/src/TimeList.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/src/TimeList.cpp.o.requires

CMakeFiles/ServerD.dir/src/TimeList.cpp.o.provides: CMakeFiles/ServerD.dir/src/TimeList.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/src/TimeList.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/src/TimeList.cpp.o.provides

CMakeFiles/ServerD.dir/src/TimeList.cpp.o.provides.build: CMakeFiles/ServerD.dir/src/TimeList.cpp.o

CMakeFiles/ServerD.dir/src/MemPool.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/src/MemPool.cpp.o: ../src/MemPool.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/src/MemPool.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/src/MemPool.cpp.o -c /home/bailongxian/Blx/NetWorK/Server/src/MemPool.cpp

CMakeFiles/ServerD.dir/src/MemPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/src/MemPool.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Server/src/MemPool.cpp > CMakeFiles/ServerD.dir/src/MemPool.cpp.i

CMakeFiles/ServerD.dir/src/MemPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/src/MemPool.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Server/src/MemPool.cpp -o CMakeFiles/ServerD.dir/src/MemPool.cpp.s

CMakeFiles/ServerD.dir/src/MemPool.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/src/MemPool.cpp.o.requires

CMakeFiles/ServerD.dir/src/MemPool.cpp.o.provides: CMakeFiles/ServerD.dir/src/MemPool.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/src/MemPool.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/src/MemPool.cpp.o.provides

CMakeFiles/ServerD.dir/src/MemPool.cpp.o.provides.build: CMakeFiles/ServerD.dir/src/MemPool.cpp.o

CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o: ../src/Main_Reactor.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o -c /home/bailongxian/Blx/NetWorK/Server/src/Main_Reactor.cpp

CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Server/src/Main_Reactor.cpp > CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.i

CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Server/src/Main_Reactor.cpp -o CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.s

CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o.requires

CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o.provides: CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o.provides

CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o.provides.build: CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o

CMakeFiles/ServerD.dir/src/Accept.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/src/Accept.cpp.o: ../src/Accept.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/src/Accept.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/src/Accept.cpp.o -c /home/bailongxian/Blx/NetWorK/Server/src/Accept.cpp

CMakeFiles/ServerD.dir/src/Accept.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/src/Accept.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Server/src/Accept.cpp > CMakeFiles/ServerD.dir/src/Accept.cpp.i

CMakeFiles/ServerD.dir/src/Accept.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/src/Accept.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Server/src/Accept.cpp -o CMakeFiles/ServerD.dir/src/Accept.cpp.s

CMakeFiles/ServerD.dir/src/Accept.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/src/Accept.cpp.o.requires

CMakeFiles/ServerD.dir/src/Accept.cpp.o.provides: CMakeFiles/ServerD.dir/src/Accept.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/src/Accept.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/src/Accept.cpp.o.provides

CMakeFiles/ServerD.dir/src/Accept.cpp.o.provides.build: CMakeFiles/ServerD.dir/src/Accept.cpp.o

CMakeFiles/ServerD.dir/src/CSocket.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/src/CSocket.cpp.o: ../src/CSocket.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/src/CSocket.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/src/CSocket.cpp.o -c /home/bailongxian/Blx/NetWorK/Server/src/CSocket.cpp

CMakeFiles/ServerD.dir/src/CSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/src/CSocket.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Server/src/CSocket.cpp > CMakeFiles/ServerD.dir/src/CSocket.cpp.i

CMakeFiles/ServerD.dir/src/CSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/src/CSocket.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Server/src/CSocket.cpp -o CMakeFiles/ServerD.dir/src/CSocket.cpp.s

CMakeFiles/ServerD.dir/src/CSocket.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/src/CSocket.cpp.o.requires

CMakeFiles/ServerD.dir/src/CSocket.cpp.o.provides: CMakeFiles/ServerD.dir/src/CSocket.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/src/CSocket.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/src/CSocket.cpp.o.provides

CMakeFiles/ServerD.dir/src/CSocket.cpp.o.provides.build: CMakeFiles/ServerD.dir/src/CSocket.cpp.o

CMakeFiles/ServerD.dir/src/Connect.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/src/Connect.cpp.o: ../src/Connect.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/src/Connect.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/src/Connect.cpp.o -c /home/bailongxian/Blx/NetWorK/Server/src/Connect.cpp

CMakeFiles/ServerD.dir/src/Connect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/src/Connect.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Server/src/Connect.cpp > CMakeFiles/ServerD.dir/src/Connect.cpp.i

CMakeFiles/ServerD.dir/src/Connect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/src/Connect.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Server/src/Connect.cpp -o CMakeFiles/ServerD.dir/src/Connect.cpp.s

CMakeFiles/ServerD.dir/src/Connect.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/src/Connect.cpp.o.requires

CMakeFiles/ServerD.dir/src/Connect.cpp.o.provides: CMakeFiles/ServerD.dir/src/Connect.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/src/Connect.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/src/Connect.cpp.o.provides

CMakeFiles/ServerD.dir/src/Connect.cpp.o.provides.build: CMakeFiles/ServerD.dir/src/Connect.cpp.o

CMakeFiles/ServerD.dir/src/Epoll.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/src/Epoll.cpp.o: ../src/Epoll.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/src/Epoll.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/src/Epoll.cpp.o -c /home/bailongxian/Blx/NetWorK/Server/src/Epoll.cpp

CMakeFiles/ServerD.dir/src/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/src/Epoll.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Server/src/Epoll.cpp > CMakeFiles/ServerD.dir/src/Epoll.cpp.i

CMakeFiles/ServerD.dir/src/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/src/Epoll.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Server/src/Epoll.cpp -o CMakeFiles/ServerD.dir/src/Epoll.cpp.s

CMakeFiles/ServerD.dir/src/Epoll.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/src/Epoll.cpp.o.requires

CMakeFiles/ServerD.dir/src/Epoll.cpp.o.provides: CMakeFiles/ServerD.dir/src/Epoll.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/src/Epoll.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/src/Epoll.cpp.o.provides

CMakeFiles/ServerD.dir/src/Epoll.cpp.o.provides.build: CMakeFiles/ServerD.dir/src/Epoll.cpp.o

CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o: /home/bailongxian/Blx/NetWorK/Public/error.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o   -c /home/bailongxian/Blx/NetWorK/Public/error.c

CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/bailongxian/Blx/NetWorK/Public/error.c > CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.i

CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/bailongxian/Blx/NetWorK/Public/error.c -o CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.s

CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o.requires:
.PHONY : CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o.requires

CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o.provides: CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o.provides

CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o.provides.build: CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o

CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o: CMakeFiles/ServerD.dir/flags.make
CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o: /home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o -c /home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp

CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp > CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.i

CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp -o CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.s

CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o.requires:
.PHONY : CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o.requires

CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o.provides: CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerD.dir/build.make CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o.provides.build
.PHONY : CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o.provides

CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o.provides.build: CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o

# Object files for target ServerD
ServerD_OBJECTS = \
"CMakeFiles/ServerD.dir/Main.cpp.o" \
"CMakeFiles/ServerD.dir/src/EventLoop.cpp.o" \
"CMakeFiles/ServerD.dir/src/Message.cpp.o" \
"CMakeFiles/ServerD.dir/src/Connector.cpp.o" \
"CMakeFiles/ServerD.dir/src/Common.cpp.o" \
"CMakeFiles/ServerD.dir/src/TimeList.cpp.o" \
"CMakeFiles/ServerD.dir/src/MemPool.cpp.o" \
"CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o" \
"CMakeFiles/ServerD.dir/src/Accept.cpp.o" \
"CMakeFiles/ServerD.dir/src/CSocket.cpp.o" \
"CMakeFiles/ServerD.dir/src/Connect.cpp.o" \
"CMakeFiles/ServerD.dir/src/Epoll.cpp.o" \
"CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o" \
"CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o"

# External object files for target ServerD
ServerD_EXTERNAL_OBJECTS =

ServerD: CMakeFiles/ServerD.dir/Main.cpp.o
ServerD: CMakeFiles/ServerD.dir/src/EventLoop.cpp.o
ServerD: CMakeFiles/ServerD.dir/src/Message.cpp.o
ServerD: CMakeFiles/ServerD.dir/src/Connector.cpp.o
ServerD: CMakeFiles/ServerD.dir/src/Common.cpp.o
ServerD: CMakeFiles/ServerD.dir/src/TimeList.cpp.o
ServerD: CMakeFiles/ServerD.dir/src/MemPool.cpp.o
ServerD: CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o
ServerD: CMakeFiles/ServerD.dir/src/Accept.cpp.o
ServerD: CMakeFiles/ServerD.dir/src/CSocket.cpp.o
ServerD: CMakeFiles/ServerD.dir/src/Connect.cpp.o
ServerD: CMakeFiles/ServerD.dir/src/Epoll.cpp.o
ServerD: CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o
ServerD: CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o
ServerD: CMakeFiles/ServerD.dir/build.make
ServerD: CMakeFiles/ServerD.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ServerD"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ServerD.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ServerD.dir/build: ServerD
.PHONY : CMakeFiles/ServerD.dir/build

CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/Main.cpp.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/src/EventLoop.cpp.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/src/Message.cpp.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/src/Connector.cpp.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/src/Common.cpp.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/src/TimeList.cpp.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/src/MemPool.cpp.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/src/Main_Reactor.cpp.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/src/Accept.cpp.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/src/CSocket.cpp.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/src/Connect.cpp.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/src/Epoll.cpp.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/error.c.o.requires
CMakeFiles/ServerD.dir/requires: CMakeFiles/ServerD.dir/home/bailongxian/Blx/NetWorK/Public/Blowfish.cpp.o.requires
.PHONY : CMakeFiles/ServerD.dir/requires

CMakeFiles/ServerD.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ServerD.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ServerD.dir/clean

CMakeFiles/ServerD.dir/depend:
	cd /home/bailongxian/Blx/NetWorK/Server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bailongxian/Blx/NetWorK/Server /home/bailongxian/Blx/NetWorK/Server /home/bailongxian/Blx/NetWorK/Server/build /home/bailongxian/Blx/NetWorK/Server/build /home/bailongxian/Blx/NetWorK/Server/build/CMakeFiles/ServerD.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ServerD.dir/depend
