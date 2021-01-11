cmake_minimum_required(VERSION 3.0.0)
project(ode_solver VERSION 0.1.0)

add_definitions(-std=c++14)

add_executable(ode_solver			
"./main.cpp"
"./eeSolver.cpp"
"./ieSolver.cpp"
)
