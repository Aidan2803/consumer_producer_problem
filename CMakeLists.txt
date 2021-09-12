cmake_minimum_required(VERSION 3.20.2)

project(ConsumerProducerProblem)

SET(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(headers)

file(GLOB SOURCES "*.cpp")

add_executable(CPP ${SOURCES})

