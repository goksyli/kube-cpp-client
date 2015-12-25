file(GLOB
    SRC_FILES
    "*.cpp")

find_package(CURL REQUIRED)
if( CURL_FOUND )
    include_directories(${CURL_INCLUDE_DIR}
                        ${KUBE_CLI_INC})
endif()


add_library(${KUBE_CLI_LIB} ${SRC_FILES})
target_link_libraries(${KUBE_CLI_LIB} ${CURL_LIBRARY})
