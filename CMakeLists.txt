project(cryptopass C CXX)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)

set(cryptopass_VERSION_MAJOR 0)
set(cryptopass_VERSION_MINOR 1)
set(cryptopass_VERSION_PATCH 0)
set(cryptopass_VERSION_TWEAK 0)

execute_process(COMMAND git submodule update --init)
add_library(fastpbkdf2 STATIC
						lib/fastpbkdf2/fastpbkdf2.c)
add_library(cpp-base64 STATIC
						lib/cpp-base64/base64.cpp)

add_executable(
	cryptopass
	src/main.cpp
)

target_link_libraries(cryptopass fastpbkdf2 cpp-base64 crypto)
