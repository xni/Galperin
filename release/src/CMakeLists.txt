cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

set (PROJECT ode_solve)
project (${PROJECT})

set (HEADERS
  function.h
  optimisation.h
  restrictions.h
  problem_types/approximator.h
  MQ/MQ_1.h)

set (SOURCES
  optimisation.cpp
  problem_types/approximator.cpp
  MQ/MQ_1.cpp
  main.cpp)

add_executable (${PROJECT} ${HEADERS} ${SOURCES})
