cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter08)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(IMGCODEC_EXAMPLE_FILE "imgcodec_example.cc")

# 生成可执行文件
add_executable(imgcodec_example ${IMGCODEC_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(imgcodec_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS imgcodec_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(VIDEOIO_EXAMPLE_FILE "videoIO_example.cc")

# 生成可执行文件
add_executable(videoio_example ${VIDEOIO_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(videoio_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS videoio_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(DATAPERSISTENCE_EXAMPLE_FILE "dataPersistence_example.cc")

# 生成可执行文件
add_executable(dataPersistence_example ${DATAPERSISTENCE_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(dataPersistence_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS dataPersistence_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin