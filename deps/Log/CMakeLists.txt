cmake_minimum_required(VERSION 3.10)
project(Log VERSION 1.0 DESCRIPTION "Log library" LANGUAGES CXX)

file(GLOB_RECURSE LOG_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(LOG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LOG_LIBRARY Log)

set(LOG_LIBRARIES ${LOG_LIBRARY})

set(
  LOG_INCLUDE_DIR
  ${LOG_INCLUDE_DIR}
  PARENT_SCOPE
)
set(
  LOG_LIBRARIES
  ${LOG_LIBRARIES}
  PARENT_SCOPE
)

add_library(${LOG_LIBRARY} ${LOG_SRC_FILES})

target_include_directories(${LOG_LIBRARY} PUBLIC ${LOG_INCLUDE_DIR})


#add_executable(testLog tests/main.cpp)
#target_include_directories(testLog PUBLIC ${LOG_INCLUDE_DIR})
#target_link_libraries(testLog PUBLIC ${LOG_LIBRARIES})
