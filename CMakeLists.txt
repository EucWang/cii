cmake_minimum_required(VERSION 3.1)
project(CII)
set(CII_VERSION_MAJOR 1)
set(CII_VERSION_MINOR 0)
#允许gdb调试
set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
#set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS}  -O0 -Wall -g -ggdb")
 
#添加C++11支持及其他选项
#set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs -Wno-deprecated")
#set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS -g -ftest-coverage -fprofile-arcs"})
set(CMAKE_C_FLAGS "-std=c11")
include_directories(include)
include_directories(include_examples)

#指明本项目包含一个子目录 src misc examples
add_subdirectory(src)
add_subdirectory(misc)
add_subdirectory(examples)

#把当前目录(./src/  ./misc/  ./examples/)下所有源代码文件和头文件加入变量SRC_LIST
AUX_SOURCE_DIRECTORY(./src/ SRC_LIST)
AUX_SOURCE_DIRECTORY(./misc/ SRC_LIST)
AUX_SOURCE_DIRECTORY(./examples/ SRC_LIST)

#生成可执行文件
add_executable(cii ${SRC_LIST} main.c)
 
#添加链接库
 
#function(assign_source_group)
 #   foreach(_source IN ITEMS ${ARGN})
 #       if (IS_ABSOLUTE "${_source}")
 #           file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
  #      else()
 #           set(_source_rel "${_source}")
 #       endif()
 #       get_filename_component(_source_path "${_source_rel}" PATH)
 #       string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
 #       source_group("${_source_path_msvc}" FILES "${_source}")
 #   endforeach()
#endfunction(assign_source_group)
 
#function(my_add_executable)
 #   foreach(_source IN ITEMS ${ARGN})
 #       assign_source_group(${_source})
 #   endforeach()
 #   add_executable(${ARGV})
#endfunction(my_add_executable)
 
# my_add_executable(cii examples/basename.c)