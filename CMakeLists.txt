CMAKE_MINIMUM_REQUIRED(VERSION 3.10) # for windows XP compatibility
PROJECT(mdict-cpp VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17) # for windows XP compatibility
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_subdirectory(deps/miniz)
add_subdirectory(deps/minilzo)

# Library target: mdict
ADD_LIBRARY(mdict STATIC src/mdict.cc src/binutils.cc src/ripemd128.c src/adler32.cc src/mdict_extern.cc)
target_link_libraries(mdict PRIVATE miniz minilzo turbo::base64 ZLIB::ZLIB)


# Add include directories
target_include_directories(mdict PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${CMAKE_CURRENT_SOURCE_DIR}/deps/
)

