# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
SET(CMAKE_CXX_COMPILER "c:/mingw/bin/g++.exe")

cmake_minimum_required (VERSION 2.8.11)
project (CPPLEARNING)


# Recurse into the "src" subdirectory. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (src)
