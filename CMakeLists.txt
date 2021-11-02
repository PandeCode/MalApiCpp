cmake_minimum_required(VERSION 3.20)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS ON)

set(CMAKE_C_COMPILER /usr/bin/clang CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE PATH "" FORCE)
set(
  CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -std=c++17 -ferror-limit=0 -ftemplate-backtrace-limit=0 -fuse-ld=lld -pedantic -Wno-unused-command-line-argument -Wextra"
)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

project(MalApi VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "My anime list c++ api library with tests and sample project.")

include_directories(${CMAKE_SOURCE_DIR}/include)

include(cotire)

add_subdirectory(malapi)
add_subdirectory(MalApiTest)
add_subdirectory(GetDubs)
