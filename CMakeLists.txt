cmake_minimum_required (VERSION 2.6)
project (Disty)

file (GLOB SRC_FILES "src/*.cpp")
include_directories ("headers")

add_executable (disty ${SRC_FILES})
