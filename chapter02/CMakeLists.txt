cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter2)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(image_show_file "image_show.cc")

# 生成可执行文件
add_executable(image_show ${image_show_file})

# 添加可执行文件使用的链接库
target_link_libraries(image_show ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS image_show DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin)

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(video_show_file "video_show.cc")

# 生成可执行文件
add_executable(video_show ${video_show_file})

# 添加可执行文件使用的链接库
target_link_libraries(video_show ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS video_show DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin)

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(video_tracker_show_file "video_tracker_show.cc")

# 生成可执行文件
add_executable(video_tracker_show ${video_tracker_show_file})

# 添加可执行文件使用的链接库
target_link_libraries(video_tracker_show ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS video_tracker_show DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(image_transform_file "image_transform.cc")

# 生成可执行文件
add_executable(image_transform ${image_transform_file})

# 添加可执行文件使用的链接库
target_link_libraries(image_transform ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS image_transform DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(video_writer_file "video_writer.cc")

# 生成可执行文件
add_executable(video_writer ${video_writer_file})

# 添加可执行文件使用的链接库
target_link_libraries(video_writer ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS video_writer DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

