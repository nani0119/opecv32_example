cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME chapter22)

# 添加链接库
# set(EXTRA_LIBS ${EXTRA_LIBS} "${OpenCV_LIBS}")


# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(CASCADECLASSIFIER_EXAMPLE_FILE "cascadeClassifier_example.cc")

# 生成可执行文件
add_executable(cascadeClassifier_example ${CASCADECLASSIFIER_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(cascadeClassifier_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS cascadeClassifier_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(DPMDETECTOR_EXAMPLE_FILE "DPMDetector_example.cc")

# 生成可执行文件
add_executable(DPMDetector_example ${DPMDETECTOR_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(DPMDetector_example ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS DPMDetector_example DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin

# ======================================================
# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(BAGOFWORDS_CLASSIFICATION_EXAMPLE_FILE "bagofwords_classification.cc")

# 生成可执行文件
add_executable(bagofwords_classification ${BAGOFWORDS_CLASSIFICATION_EXAMPLE_FILE})

# 添加可执行文件使用的链接库
target_link_libraries(bagofwords_classification ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS bagofwords_classification DESTINATION bin)
#install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/test.cnf" DESTINATION bin