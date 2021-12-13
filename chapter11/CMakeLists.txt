cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter11)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(UNIFORM_RESIZE_EXAMPLE_FILE "uniform_resize_example.cc")

# 生成可执行文件
add_executable(uniform_resize_example ${UNIFORM_RESIZE_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(uniform_resize_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS uniform_resize_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(NONUNIFORM_MAPPING_EXAMPLE_FILE "nonuniform_mapping_example.cc")

# 生成可执行文件
add_executable(nonuniform_mapping_example ${NONUNIFORM_MAPPING_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(nonuniform_mapping_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS nonuniform_mapping_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin


# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(GENERAL_MAPPING_EXAMPLE_FILE "general_mapping_example.cc")

# 生成可执行文件
add_executable(general_mapping_example ${GENERAL_MAPPING_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(general_mapping_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS general_mapping_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(IMAGE_REPAIR_EXAMPLE_FILE "image_repair_example.cc")

# 生成可执行文件
add_executable(image_repair_example ${IMAGE_REPAIR_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(image_repair_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS image_repair_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(EQUALIZEHIST_EXAMPLE_FILE "equalizeHist_example.cc")

# 生成可执行文件
add_executable(equalizeHist_example ${EQUALIZEHIST_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(equalizeHist_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS equalizeHist_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin