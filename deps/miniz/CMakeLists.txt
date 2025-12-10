SET(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "Minimum OS X deployment version")
PROJECT(miniz C)
cmake_minimum_required(VERSION 3.10)

set(miniz_SOURCE miniz.c miniz_zip.c miniz_tinfl.c miniz_tdef.c)

add_library(miniz ${miniz_SOURCE})