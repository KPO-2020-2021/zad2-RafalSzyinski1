cmake_minimum_required(VERSION 3.1)
project(complex)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(tst)
add_subdirectory(lib/googletest-master)

include_directories(inc)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true inc/*.h src/*.cpp)
set(SOURCE ${SOURCES})

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES})
add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCE})

