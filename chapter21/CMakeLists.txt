cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter21)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(SVM_EXAMPLE_FILE "svm_example.cc")

# 生成可执行文件
add_executable(svm_example ${SVM_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(svm_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS svm_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(DECISIONTREE_EXAMPLE_FILE "decisionTree_example.cc")

# 生成可执行文件
add_executable(decisionTree_example ${DECISIONTREE_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(decisionTree_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS decisionTree_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(LETTER_RECOG_EXAMPLE_FILE "letter_recog.cc")

# 生成可执行文件
add_executable(letter_recog ${LETTER_RECOG_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(letter_recog ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS letter_recog DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin
