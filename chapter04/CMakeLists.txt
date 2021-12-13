cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter4)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(exercises04_file "exercises04.cc")

# 生成可执行文件
add_executable(exercises04 ${exercises04_file})

# 添加可执行文件使用的链接库
target_link_libraries(exercises04 ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS exercises04 DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(MAT_EXAMPLE_FILE "mat_example.cc")

# 生成可执行文件
add_executable(mat_example ${MAT_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(mat_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS mat_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin
