cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter10)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

## ======================================================
## 自动包含当前目录代码文件
## aux_source_directory(. DIR_SRCS)
set(MAKE_BORDER_EXAMPLE_FILE "make_border_example.cc")
#
## 生成可执行文件
add_executable(make_border_example ${MAKE_BORDER_EXAMPLE_FILE})
#
## 添加可执行文件使用的链接库
target_link_libraries(make_border_example ${EXTRA_LIBS})
#
## 指定安装的文件信息
install(TARGETS make_border_example DESTINATION bin)
##install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin
#
## ======================================================
## 自动包含当前目录代码文件
## aux_source_directory(. DIR_SRCS)
set(THRESHOLD_EXAMPLE_FILE "threshold_example.cc")
#
## 生成可执行文件
add_executable(threshold_example ${THRESHOLD_EXAMPLE_FILE})
#
## 添加可执行文件使用的链接库
target_link_libraries(threshold_example ${EXTRA_LIBS})
#
## 指定安装的文件信息
install(TARGETS threshold_example DESTINATION bin)

#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin
# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(BLUR_EXAMPLE_FILE "blur_example.cc")

# 生成可执行文件
add_executable(blur_example ${BLUR_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(blur_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS blur_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

## ======================================================
## 自动包含当前目录代码文件
## aux_source_directory(. DIR_SRCS)
set(DERIVATIVE_EXAMPLE_FILE "derivative_example.cc")
#
## 生成可执行文件
add_executable(derivative_example ${DERIVATIVE_EXAMPLE_FILE})
#
## 添加可执行文件使用的链接库
target_link_libraries(derivative_example ${EXTRA_LIBS})
#
## 指定安装的文件信息
install(TARGETS derivative_example DESTINATION bin)
##install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

## ======================================================
## 自动包含当前目录代码文件
## aux_source_directory(. DIR_SRCS)
set(MORPHOLOGY_EXAMPLE_FILE "morphology_example.cc")
#
## 生成可执行文件
add_executable(morphology_example ${MORPHOLOGY_EXAMPLE_FILE})
#
## 添加可执行文件使用的链接库
target_link_libraries(morphology_example ${EXTRA_LIBS})
#
## 指定安装的文件信息
install(TARGETS morphology_example DESTINATION bin)
##install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin
#
#
# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(FILTER2D_EXAMPLE_FILE "filter2D_example.cc")

# 生成可执行文件
add_executable(filter2D_example ${FILTER2D_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(filter2D_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS filter2D_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin