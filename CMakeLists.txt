cmake_minimum_required(VERSION 2.8.8)

project(kube-cpp-client CXX)

set(KUBE_CLI_INC ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")
#set(KUBE_CLI_INC ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")



add_subdirectory(${PROJECT_SOURCE_DIR}/ext)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
