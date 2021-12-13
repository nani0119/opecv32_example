cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter17)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(OpticalFlow_EXAMPLE_FILE "OpticalFlow_example.cc")

# 生成可执行文件
add_executable(OpticalFlow_example ${OpticalFlow_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(OpticalFlow_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS OpticalFlow_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(meanShit_Tracking_EXAMPLE_FILE "meanShit_tracking_example.cc")

# 生成可执行文件
add_executable(meanShit_tracking_example ${meanShit_Tracking_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(meanShit_tracking_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS meanShit_tracking_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(ShiftMethod_EXAMPLE_FILE "ShiftMethod_example.cc")

# 生成可执行文件
add_executable(shiftMethod_example ${ShiftMethod_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(shiftMethod_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS shiftMethod_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(MotionTemplete_EXAMPLE_FILE "motionTemplete_example.cc")

# 生成可执行文件
add_executable(motionTemplete_example ${MotionTemplete_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(motionTemplete_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS motionTemplete_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(KalmanFilter_EXAMPLE_FILE "kalmanFilter_example.cc")

# 生成可执行文件
add_executable(kalmanFilter_example ${KalmanFilter_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(kalmanFilter_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS kalmanFilter_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(SELECTROI_EXAMPLE_FILE "selectRoi_example.cc")

# 生成可执行文件
add_executable(selectRoi_example ${SELECTROI_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(selectRoi_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS selectRoi_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin