file(GLOB KUBE_CLI_SRC_FILES *.cpp)

include_directories(${RESTLESS_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
    ${KUBE_CLI_INC})

target_link_libraries(client_cli
    ${RESTLESS_LIBRARIES})

add_executable(client_cli ${KUBE_CLI_SRC_FILES})
