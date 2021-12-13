# 设置需要的cmake版本
cmake_minimum_required(VERSION 3.10)

# 设置工程名称
project(opencv)

# 设置版本信息，在.in文件中通过@<name>@替换对应值
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

find_package(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")
# 设置需要链接的系统库
# set(REQ_LIBS ${REQ_LIBS} "m")
# set(CMAKE_REQUIRED_LIBRARIES ${REQ_LIBS})

# 检查函数功能是否存在，在配置.in文件定义该宏值
# include(CheckFunctionExists)
# check_function_exists(log HAVE_LOG)
# check_function_exists(exp HAVE_EXP)

# 定义默认选项
# option(USE_MYMATH
#	    "Use tutorial provided math implementation"
#	    on)
option(BUILD_DEBUG_TYPE
	   "build debug type"
	   on)

# 生成编译时的配置文件.h(包含各种宏)
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
	)
include_directories(${PROJECT_BINARY_DIR})

# 检查对应选项是否打开
if (BUILD_DEBUG_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb -fpermissive -std=c++11")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -fpermissive -std=c++11")
endif (BUILD_DEBUG_TYPE)

# if (USE_MYMATH)
#     add_subdirectory(MathFunctions)
#     include_directories(${PROJECT_SOURCE_DIR}/MathFunctions)
#     set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
# endif(USE_MYMATH)

# ==============================================================
# 添加头文件路径
add_subdirectory(chapter01)
add_subdirectory(chapter02)
add_subdirectory(chapter04)
add_subdirectory(chapter05)
add_subdirectory(chapter06)
add_subdirectory(chapter07)
add_subdirectory(chapter08)
add_subdirectory(chapter09)
add_subdirectory(chapter10)
add_subdirectory(chapter11)
add_subdirectory(chapter12)
add_subdirectory(chapter13)
add_subdirectory(chapter14)
add_subdirectory(chapter15)
add_subdirectory(chapter16)
add_subdirectory(chapter17)
add_subdirectory(chapter18)
add_subdirectory(chapter19)
add_subdirectory(chapter21)
add_subdirectory(chapter22)
# =============================================================

#指定安装时使用的路径前缀
set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install")
