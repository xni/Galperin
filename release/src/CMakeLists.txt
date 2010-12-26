cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

set (PROJECT ode_solve)
project (${PROJECT})

set (HEADERS
  function.h
  optimisation.h
  restrictions.h
  normal_distribution.h
  problem_types/approximator.h
  problem_types/sd_approximator.h
  problem_types/find_source.h
  MQ/MQ_1.h)

set (SOURCES
  optimisation.cpp
  problem_types/approximator.cpp
  problem_types/sd_approximator.cpp
  problem_types/find_source.cpp
  MQ/MQ_1.cpp
  main.cpp)

add_executable (${PROJECT} ${HEADERS} ${SOURCES})
set_target_properties(${PROJECT} PROPERTIES COMPLIE_FLAGS O3)
