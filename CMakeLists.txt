cmake_minimum_required(VERSION 3.10)
project(Scheduler C)

set(CMAKE_C_STANDARD 99)

# Enable compiler warnings like in Makefile
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Source files
set(SOURCES driver.c list.c CPU.c)
set(HEADERS list.h cpu.h)

# Create separate executables for each scheduling algorithm
add_executable(rr ${SOURCES} schedule_rr.c)
add_executable(fcfs ${SOURCES} schedule_fcfs.c
        schedule_rr.c)
add_executable(sjf ${SOURCES} schedule_sjf.c)
add_executable(priority ${SOURCES} schedule_priority.c)
add_executable(priority_rr ${SOURCES} schedule_priority_rr.c)
