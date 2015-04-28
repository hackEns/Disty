cmake_minimum_required (VERSION 2.6)
project (Disty)

add_definitions(-std=gnu++0x)

file (GLOB SRC_FILES "src/*.cpp")
include_directories ("headers")

add_executable (disty ${SRC_FILES})
target_link_libraries(disty wiringPi)
