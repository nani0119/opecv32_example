cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter19)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(FINDHOMOGRAPHY_EXAMPLE_FILE "findHomography_example.cc")

# 生成可执行文件
add_executable(findHomography_example ${FINDHOMOGRAPHY_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(findHomography_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS findHomography_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(BIRDEYEVIEW_EXAMPLE_FILE "birdEyeView_example.cc")

# 生成可执行文件
add_executable(birdEyeView_example ${BIRDEYEVIEW_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(birdEyeView_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS birdEyeView_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(FINDFUNDAMENTALMAT_EXAMPLE_FILE "findFundamentalMat_example.cc")

# 生成可执行文件
add_executable(findFundamentalMat_example ${FINDFUNDAMENTALMAT_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(findFundamentalMat_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS findFundamentalMat_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(STEREOCVALIBRATION_EXAMPLE_FILE "stereoCValibration_example.cc")

# 生成可执行文件
add_executable(stereoCValibration_example ${STEREOCVALIBRATION_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(stereoCValibration_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS stereoCValibration_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bino

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(Two-dimensionalLineFitting_example_file "TwoDimensionalLineFitting_example.cc")

# 生成可执行文件
add_executable(twoDimensionalLineFitting_example ${Two-dimensionalLineFitting_example_file})

# 添加可执行文件使用的链接库
target_link_libraries(twoDimensionalLineFitting_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS twoDimensionalLineFitting_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin