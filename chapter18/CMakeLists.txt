cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter18)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(CALIBRATING_CAMERA_FROM_DISK_EXAMPLE_FILE "calibrating_camera_from_disk_example.cc")

# 生成可执行文件
add_executable(calibrating_camera_from_disk_example ${CALIBRATING_CAMERA_FROM_DISK_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(calibrating_camera_from_disk_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS calibrating_camera_from_disk_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(CALIBRATING_CAMERA_EXAMPLE_FILE "calibrating_camera_example.cc")

# 生成可执行文件
add_executable(calibrating_camera_example ${CALIBRATING_CAMERA_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(calibrating_camera_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS calibrating_camera_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

