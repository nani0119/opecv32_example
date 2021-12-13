cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter14)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(CONNECTED_COMPONENTS_EXAMPLE_FILE "connectedComponents_example.cc")

# 生成可执行文件
add_executable(connectedComponents_example ${CONNECTED_COMPONENTS_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(connectedComponents_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS connectedComponents_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(APPROX_POLY_DP_EXAMPLE_FILE "approxPolyDP_example.cc")

# 生成可执行文件
add_executable(approxPolyDP_example ${APPROX_POLY_DP_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(approxPolyDP_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS approxPolyDP_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin