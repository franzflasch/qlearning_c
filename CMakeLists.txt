cmake_minimum_required(VERSION 3.0)

project (qlearning_c)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories(.)
add_library(qtable SHARED qtable.c)
target_include_directories(qtable PUBLIC .)

add_executable(qlearning qlearning.c game.c)
target_include_directories(qtable PUBLIC .)
target_link_libraries(qlearning qtable)

install (TARGETS qlearning qtable
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)

### Debian Package generation
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION "0.1.0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "https://github.com/franzflasch")
include(CPack)
