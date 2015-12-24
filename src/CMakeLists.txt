file(GLOB
    SRC_FILES
    "*.cpp")



add_library(${KUBE_CLI_LIB} ${SRC_FILES})
