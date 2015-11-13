file(GLOB KUBE_CLI_SRC_FILES *.cpp)

include_directories(${RESTLESS_INCLUDE_DIRS}
    ${KUBE_CLI_INC}
    ${RESTLESS_SOURCE_DIR}/ext/json/src)

message(STATUS "restless lib is ${RESTLESS_LIBRARIES}")

add_executable(client_cli ${KUBE_CLI_SRC_FILES})

target_link_libraries(client_cli
    ${RESTLESS_LIBRARIES})
