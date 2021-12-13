cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter16)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(CORNER_EXAMPLE_FILE "corner_example.cc")

# 生成可执行文件
add_executable(corner_example ${CORNER_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(corner_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS corner_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin
# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(CALC_OPTICAL_FLOW_PYR_LK_EXAMPLE_FILE "calcOpticalFlowPyrLK_example.cc")

# 生成可执行文件
add_executable(calcOpticalFlowPyrLK_example ${CALC_OPTICAL_FLOW_PYR_LK_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(calcOpticalFlowPyrLK_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS calcOpticalFlowPyrLK_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(GFTTDetector_EXAMPLE_FILE "GFTTDetector_example.cc")

# 生成可执行文件
add_executable(GFTTDetector_example ${GFTTDetector_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(GFTTDetector_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS GFTTDetector_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bi

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(SIMPLEBLOBDetector_EXAMPLE_FILE "SimpleBlobDetector_example.cc")

# 生成可执行文件
add_executable(SimpleBlobDetector_example ${SIMPLEBLOBDetector_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(SimpleBlobDetector_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS SimpleBlobDetector_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bi

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(FastFeatureDetector_EXAMPLE_FILE "FastFeatureDetector_example.cc")

# 生成可执行文件
add_executable(FastFeatureDetector_example ${FastFeatureDetector_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(FastFeatureDetector_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS FastFeatureDetector_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bi

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(SIFT_EXAMPLE_FILE "SIFT_example.cc")

# 生成可执行文件
add_executable(SIFT_example ${SIFT_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(SIFT_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS SIFT_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bi

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(SURF_EXAMPLE_FILE "SURF_example.cc")

# 生成可执行文件
add_executable(SURF_example ${SURF_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(SURF_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS SURF_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bi

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(StarDetector_EXAMPLE_FILE "StarDetector_example.cc")

# 生成可执行文件
add_executable(StartDetector_example ${StarDetector_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(StartDetector_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS StartDetector_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bi

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(BRISK_EXAMPLE_FILE "BRISK_example.cc")

# 生成可执行文件
add_executable(BRISK_example ${BRISK_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(BRISK_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS BRISK_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bi

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(ORB_EXAMPLE_FILE "ORB_example.cc")

# 生成可执行文件
add_executable(ORB_example ${ORB_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(ORB_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS ORB_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bi

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(FREAK_EXAMPLE_FILE "FREAK_example.cc")

# 生成可执行文件
add_executable(FREAK_example ${FREAK_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(FREAK_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS FREAK_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(DRAWKEYPOINTS_EXAMPLE_FILE "drawKeypoints_example.cc")

# 生成可执行文件
add_executable(drawKeypoints_example ${DRAWKEYPOINTS_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(drawKeypoints_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS drawKeypoints_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin