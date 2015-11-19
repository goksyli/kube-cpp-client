

include_directories(${RESTLESS_INCLUDE_DIRS}
    ${KUBE_CLI_INC}
    ${RESTLESS_SOURCE_DIR}/ext/json/src)


set(test1_SRCS test1.cpp)
add_executable(test1 ${test1_SRCS})
target_link_libraries(test1 
    ${KUBE_CLI_LIB}
    ${CURL_LIBRARIES})
