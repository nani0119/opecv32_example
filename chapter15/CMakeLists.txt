cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter15)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(SCENE_MODELING_EXAMPLE_FILE "scene_modeling_example.cc")

# 生成可执行文件
add_executable(scene_modeling_example ${SCENE_MODELING_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(scene_modeling_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS scene_modeling_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(ACERAGING_BACKGROUND_METHOD_EXAMPLE_FILE "averaging_background_method_example.cc")

# 生成可执行文件
add_executable(averaging_background_method_example ${ACERAGING_BACKGROUND_METHOD_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(averaging_background_method_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS averaging_background_method_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(CODEBOOK_BACKGROUND_METHOD_EXAMPLE_FILE "codebook_background_method_example.cc")

# 生成可执行文件
add_executable(codebook_background_method_example ${CODEBOOK_BACKGROUND_METHOD_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(codebook_background_method_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS codebook_background_method_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin