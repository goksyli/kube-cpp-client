

include_directories(${RESTLESS_INCLUDE_DIRS}
    ${KUBE_CLI_INC}
    ${RESTLESS_SOURCE_DIR}/ext/json/src)


set(test1_SRCS test1.cpp)
add_executable(test1 ${test1_SRCS})
target_link_libraries(test1 
    ${KUBE_CLI_LIB}
    ${CURL_LIBRARIES})

set(test2_SRCS test2.cpp)
add_executable(test2 ${test2_SRCS})
target_link_libraries(test2
    ${KUBE_CLI_LIB})

set(test3_SRCS test3.cpp)
add_executable(test3 ${test3_SRCS})
target_link_libraries(test3 
    ${KUBE_CLI_LIB}
    ${CURL_LIBRARIES})

set(test4_SRCS test4.cpp)
add_executable(test4 ${test4_SRCS})
target_link_libraries(test4 
    ${KUBE_CLI_LIB}
    ${CURL_LIBRARIES})

set(test5_SRCS test5.cpp)
add_executable(test5 ${test5_SRCS})
target_link_libraries(test5 
    ${KUBE_CLI_LIB}
    ${CURL_LIBRARIES})
