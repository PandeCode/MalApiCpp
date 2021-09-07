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

project(MalApi VERSION 0.1.0 DESCRIPTION "My Anime List Api Client" LANGUAGES CXX)

find_package(Threads REQUIRED)

include(${CMAKE_SOURCE_DIR}/Packages.cmake)
link_directories(${CMAKE_SOURCE_DIR}/libs)

file(
  GLOB_RECURSE
  MALAPI_SRC_FILES
  ${CMAKE_SOURCE_DIR}/src/*.cpp
)

set(
  _INCLUDE_DIRS
  ${CPR_INCLUDE_DIRS}
)
set(
  MALAPI_INCLUDE_DIRS
  ${CMAKE_SOURCE_DIR}/include
  ${_INCLUDE_DIRS}
)

set(
  _LIBRARIES
  ${CMAKE_THREAD_LIBS_INIT}
  ${CPR_LIBRARIES}
)

set(MALAPI_LIBRARY malapi)
set(MALAPI_LIBRARIES ${MALAPI_LIBRARY})

message("MALAPI_INCLUDE_DIRS    : " ${MALAPI_INCLUDE_DIRS})
message("MALAPI_LIBRARIES       : " ${MALAPI_LIBRARIES})
message("MALAPI_LIBRARY         : " ${MALAPI_LIBRARY})
message("MALAPI_SRC_FILES       : " ${MALAPI_SRC_FILES})
message("_LIBRARIES             : " ${_LIBRARIES})

add_library(${MALAPI_LIBRARY} ${MALAPI_SRC_FILES})

target_compile_options(${MALAPI_LIBRARY} PUBLIC -pthread)
target_link_libraries(${MALAPI_LIBRARY} PRIVATE ${_LIBRARIES})
target_include_directories(${MALAPI_LIBRARY} PRIVATE ${MALAPI_INCLUDE_DIRS})

add_subdirectory(tests)
