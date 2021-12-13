cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter13)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(CALC_HIST_EXAMPLE_FILE "calcHist_example.cc")

# 生成可执行文件
add_executable(calcHist_example ${CALC_HIST_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(calcHist_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS calcHist_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(COMPARE_HIST_EXAMPLE_FILE "compareHist_example.cc")

# 生成可执行文件
add_executable(compareHist_example ${COMPARE_HIST_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(compareHist_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS compareHist_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(HIST_EXAMPLE_FILE "hist_example.cc")

# 生成可执行文件
add_executable(hist_example ${HIST_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(hist_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS hist_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bi

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(BACKPROJECTION_EXAMPLE_FILE "backprojection_example.cc")

# 生成可执行文件
add_executable(backprojection_example ${BACKPROJECTION_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(backprojection_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS backprojection_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bi

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(MATCHTEMPLATE_EXAMPLE_FILE "matchTemplate_example.cc")

# 生成可执行文件
add_executable(matchtemplate_example ${MATCHTEMPLATE_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(matchtemplate_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS matchtemplate_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bi