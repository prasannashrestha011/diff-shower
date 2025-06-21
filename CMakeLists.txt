cmake_minimum_required(VERSION 3.10)
project(Diff)

find_package(OpenSSL REQUIRED)
add_executable(blb blob.cpp)
add_executable(prt prt.cpp)
add_executable(vect vect.cpp)
target_link_libraries(prt PRIVATE OpenSSL::Crypto)
target_link_libraries(blb  PRIVATE OpenSSL::Crypto)
