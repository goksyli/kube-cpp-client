file(GLOB KUBE_CLI_SRCS *.cpp)

include_directories(${RESTLESS_INCLUDE_DIRS}
    ${KUBE_CLI_INC}
    ${RESTLESS_SOURCE_DIR}/ext/json/src)

message(STATUS "kubecli include is ${KUBE_CLI_INC}")

#add_executable(client_cli ${KUBE_CLI_SRC_FILES})

#target_link_libraries(client_cli
#    ${RESTLESS_LIBRARIES})

add_library(${KUBE_CLI_LIB} ${KUBE_CLI_SRCS})
