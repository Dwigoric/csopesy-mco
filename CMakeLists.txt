# CMakeList.txt : CMake project for CSOPESY MCO, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

project("CSOPESY MCO")

# Add source to this project's executable.
add_executable(CMakeTarget
        "src/console/ConsoleManager.h"
        "src/console/ConsoleManager.cpp"
        "src/console/AConsole.h"
        "src/console/MainConsole.h"
        "src/console/MainConsole.cpp"
        "src/console/BaseScreen.h"
        "src/main.h"
        "src/main.cpp"
        src/process/Process.cpp
        src/process/Process.h
        src/util/string-tokenizer.cpp
        src/util/string-tokenizer.h
        src/commands/ScreenCommand.cpp
        src/commands/ScreenCommand.h
        src/commands/ACommand.h
        src/console/BaseScreen.cpp
        src/process/AScheduler.cpp
        src/process/AScheduler.h
        src/process/FCFSScheduler.cpp
        src/process/FCFSScheduler.h
        src/threading/Thread.cpp
        src/threading/Thread.h
        src/instructions/AInstruction.h
        "src/instructions/PrintInstruction.h" "src/instructions/PrintInstruction.cpp"
        src/threading/SchedulerThread.cpp
        src/threading/SchedulerThread.h
        src/commands/SchedulerTestCommand.cpp
        src/commands/SchedulerTestCommand.h
        src/commands/SchedulerStopCommand.cpp
        src/commands/SchedulerStopCommand.h
        src/cpu/CPUWorker.h 
        src/cpu/CPUWorker.cpp
        src/cpu/CPUManager.cpp 
        src/cpu/CPUManager.h
 "src/commands/InitializeCommand.cpp" "src/commands/InitializeCommand.h" "src/commands/ExitCommand.cpp" "src/commands/ExitCommand.h" "src/commands/ReportUtilCommand.h" "src/commands/ReportUtilCommand.cpp"
        src/util/randint.h 
        src/util/randint.cpp
        src/threading/CustomThread.cpp
        src/threading/CustomThread.h
 "src/process/RoundRobinScheduler.h" "src/process/RoundRobinScheduler.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif ()

# TODO: Add tests and install targets if needed.
