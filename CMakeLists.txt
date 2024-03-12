cmake_minimum_required (VERSION 3.8)

project(16-bit-pc-emulator VERSION 0.0.1)
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_executable(out src/main.cpp)
