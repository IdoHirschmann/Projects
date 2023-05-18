cmake_minimum_required(VERSION 3.20)
project(finalProject C)

set(CMAKE_C_STANDARD 99)

add_executable(finalProject main.c treefuncs.c treefuncs.h MusiciansGroup.c MusiciansGroup.h InstrumentesPriceListFuncs.c InstrumentesPriceListFuncs.h concert.c concert.h)
