cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

set (PROJECT ode_solve)
project (${PROJECT})

set (HEADERS
        function.h)

set (SOURCES
        main.cpp)

add_executable (${PROJECT} ${HEADERS} ${SOURCES})
