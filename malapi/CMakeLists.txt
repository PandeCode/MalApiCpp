project(MalApi VERSION 0.1.0 DESCRIPTION "My Anime List Api Client" LANGUAGES CXX)

find_package(Threads REQUIRED)

file(GLOB_RECURSE __MALAPI_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE __MALAPI_TYPE_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/types/*.cpp)
set(MALAPI_SRC_FILES ${__MALAPI_TYPE_SRC_FILES} ${__MALAPI_SRC_FILES})

set(MALAPI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(MALAPI_INCLUDE_DIRS ${MALAPI_INCLUDE_DIRS} PARENT_SCOPE)

set(_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})

set(MALAPI_LIBRARY malapi)
set(MALAPI_LIBRARIES ${MALAPI_LIBRARY} PARENT_SCOPE)

message("MALAPI_INCLUDE_DIRS    : " ${MALAPI_INCLUDE_DIRS})
message("MALAPI_LIBRARIES       : " ${MALAPI_LIBRARIES})
message("MALAPI_LIBRARY         : " ${MALAPI_LIBRARY})
message("MALAPI_SRC_FILES       : " ${MALAPI_SRC_FILES})
message("_LIBRARIES             : " ${_LIBRARIES})

add_library(${MALAPI_LIBRARY} ${MALAPI_SRC_FILES})

target_compile_options(${MALAPI_LIBRARY} PUBLIC -pthread)
target_link_libraries(${MALAPI_LIBRARY} PRIVATE ${_LIBRARIES} PUBLIC ssl crypto)
target_include_directories(${MALAPI_LIBRARY} PRIVATE ${MALAPI_INCLUDE_DIRS})

target_precompile_headers(
  ${MALAPI_LIBRARY}
  PUBLIC
  <array>
  <cstdint>
  <fstream>
  <sstream>
  <iostream>
  <optional>
  <sstream>
  <type_traits>
  <variant>
  <vector>
  ${CMAKE_SOURCE_DIR}/include/cpp-httplib/httplib.hpp
  ${CMAKE_SOURCE_DIR}/include/nlohmann/json.hpp
)
