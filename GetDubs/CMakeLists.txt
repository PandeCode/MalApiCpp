set(GET_DUBS_EXECUTABLE_NAME GetDubs)

file(GLOB_RECURSE GET_DUBS_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(
  GET_DUBS_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${MALAPI_INCLUDE_DIRS}
  ${LOG_INCLUDE_DIRS}
)
set(
  GET_DUBS_LIBRARIES
  ${LOG_LIBRARIES}
  ${MALAPI_LIBRARIES}
)

message("GET_DUBS_EXECUTABLE_NAME        : " ${GET_DUBS_EXECUTABLE_NAME})
message("GET_DUBS_INCLUDE_DIRS           : " ${GET_DUBS_INCLUDE_DIRS})
message("GET_DUBS_LIBRARIES              : " ${GET_DUBS_LIBRARIES})
message("GET_DUBS_SRC_FILES              : " ${GET_DUBS_SRC_FILES})

add_executable(${GET_DUBS_EXECUTABLE_NAME} ${GET_DUBS_SRC_FILES})

target_include_directories(${GET_DUBS_EXECUTABLE_NAME} PUBLIC ${GET_DUBS_INCLUDE_DIRS})
target_link_libraries(${GET_DUBS_EXECUTABLE_NAME} PUBLIC ${GET_DUBS_LIBRARIES})
target_compile_options(${GET_DUBS_EXECUTABLE_NAME} PUBLIC -pthread)
target_precompile_headers(
  ${GET_DUBS_EXECUTABLE_NAME}
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
  ${CMAKE_CURRENT_SOURCE_DIR}/include/tabulate/tabulate.hpp
)
cotire(${MALAPI_LIBRARY})


cotire(${GET_DUBS_EXECUTABLE_NAME})
