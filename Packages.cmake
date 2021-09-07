set(FETCHCONTENT_QUIET FALSE)
include(FetchContent)

#### LOG ###
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/Log)
#### END LOG ###

### CPR ###
set(CPR_BUILD_TESTS OFF)
set(CPR_BUILD_TESTS_SSL OFF)
set(CPR_USE_SYSTEM_CURL ON)
set(BUILD_CPR_TESTS OFF)
set(CPR_USE_SYSTEM_GTEST ON)

fetchcontent_declare(
  cpr
  GIT_REPOSITORY https://github.com/whoshuu/cpr.git
  GIT_TAG fdc7c79da8ac5c4591199cb4f0ee3d06501827a5
  GIT_PROGRESS TRUE
)
fetchcontent_makeavailable(cpr)

set(CPR_INCLUDE_DIRS ${cpr_SOURCE_DIR}/include)
set(CPR_LIBRARIES cpr::cpr)
message("CPR_INCLUDE_DIRS : " ${CPR_INCLUDE_DIRS})
message("CPR_LIBRARIES    : " ${CPR_LIBRARIES})
#### END CPR ###
