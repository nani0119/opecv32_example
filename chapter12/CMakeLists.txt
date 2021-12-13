cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter12)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(DFT_EXAMPLE_FILE "dft_example.cc")

# 生成可执行文件
add_executable(dft_example ${DFT_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(dft_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS dft_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(INTEGRAL_IMAGE_EXAMPLE_FILE "integral_image_example.cc")

# 生成可执行文件
add_executable(integral_image_example ${INTEGRAL_IMAGE_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(integral_image_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS integral_image_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(CANNY_EDAGE_DETECT_EXAMPLE_FILE "canny_edage_detect_example.cc")

# 生成可执行文件
add_executable(canny_edage_detect_example ${CANNY_EDAGE_DETECT_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(canny_edage_detect_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS canny_edage_detect_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bino

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(HOUGH_TRANSFORM_EXAMPLE_FILE "hough_transform_example.cc")

# 生成可执行文件
add_executable(hough_transform_example ${HOUGH_TRANSFORM_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(hough_transform_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS hough_transform_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(DISTANCE_TRANSFORM_EXAMPLE_FILE "distance_transform_example.cc")

# 生成可执行文件
add_executable(distance_transform_example ${DISTANCE_TRANSFORM_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(distance_transform_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS distance_transform_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(SEGMENTATION_EXAMPLE_FILE "segmentation_example.cc")

# 生成可执行文件
add_executable(segmentation_example ${SEGMENTATION_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(segmentation_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS segmentation_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin