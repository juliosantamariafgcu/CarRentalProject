cmake_minimum_required(VERSION 3.25)
project(FinalProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(FinalProject CarRentalSystem.cpp Vehicle.h Customer.h RentalContract.h Date.h Person.h)
