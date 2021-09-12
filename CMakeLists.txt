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

add_subdirectory(${CMAKE_SOURCE_DIR}/deps/Log)
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

#target_precompile_headers(
  #${MALAPI_LIBRARY}
  #PUBLIC
  #<iostream>
  #<string>
  #${CMAKE_SOURCE_DIR}/include/httplib.hpp
  ##${CMAKE_SOURCE_DIR}/include/crow.h
  ##${CMAKE_SOURCE_DIR}/crow/app.h
  ##${CMAKE_SOURCE_DIR}/crow/ci_map.h
  ##${CMAKE_SOURCE_DIR}/crow/common.h
  ##${CMAKE_SOURCE_DIR}/crow/compression.h
  ##${CMAKE_SOURCE_DIR}/crow/dumb_timer_queue.h
  ##${CMAKE_SOURCE_DIR}/crow/http_connection.h
  ##${CMAKE_SOURCE_DIR}/crow/http_parser_merged.h
  ##${CMAKE_SOURCE_DIR}/crow/http_request.h
  ##${CMAKE_SOURCE_DIR}/crow/http_response.h
  ##${CMAKE_SOURCE_DIR}/crow/http_server.h
  ##${CMAKE_SOURCE_DIR}/crow/json.h
  ##${CMAKE_SOURCE_DIR}/crow/logging.h
  ##${CMAKE_SOURCE_DIR}/crow/middleware_context.h
  ##${CMAKE_SOURCE_DIR}/crow/middlewares
  ##${CMAKE_SOURCE_DIR}/crow/mime_types.h
  ##${CMAKE_SOURCE_DIR}/crow/multipart.h
  ##${CMAKE_SOURCE_DIR}/crow/mustache.h
  ##${CMAKE_SOURCE_DIR}/crow/parser.h
  ##${CMAKE_SOURCE_DIR}/crow/query_string.h
  ##${CMAKE_SOURCE_DIR}/crow/returnable.h
  ##${CMAKE_SOURCE_DIR}/crow/routing.h
  ##${CMAKE_SOURCE_DIR}/crow/settings.h
  ##${CMAKE_SOURCE_DIR}/crow/socket_adaptors.h
  ##${CMAKE_SOURCE_DIR}/crow/TinySHA1.hpp
  ##${CMAKE_SOURCE_DIR}/crow/utility.h
  ##${CMAKE_SOURCE_DIR}/crow/version.h
  ##${CMAKE_SOURCE_DIR}/crow/websocket.h
#)

add_subdirectory(tests)
