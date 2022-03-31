cmake_minimum_required(VERSION 3.13)

project(llvm_add2sub)

find_package(LLVM 13.0 REQUIRED CONFIG)

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

add_compile_options(-fno-rtti)
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(pass)
