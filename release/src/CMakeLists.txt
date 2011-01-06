cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
set(CMAKE_BUILD_TYPE Release)
set (PROJECT ode_solve)
project (${PROJECT})

set (HEADERS
  function.h
  optimisation.h
  normal_distribution.h
  problem_types/reverse_with_curvilinear_borders.h
  MQ/MQ_1.h
  MQ/MQ_2.h)

set (SOURCES
  optimisation.cpp
  problem_types/reverse_with_curvilinear_borders.cpp
  MQ/MQ_1.cpp
  MQ/MQ_2.cpp
  main.cpp)

add_executable (${PROJECT} ${HEADERS} ${SOURCES})
set_target_properties(${PROJECT} PROPERTIES COMPLIE_FLAGS O3)
