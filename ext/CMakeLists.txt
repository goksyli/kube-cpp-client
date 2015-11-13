find_package(RESTLESS)

if(NOT RESTLESS_FOUND)
    message(STATS "can't find REST in system.")
    add_subdirectory(restless)
    set(RESTLESS_FOUND TRUE)
    set(RESTLESS_LIBRARIES restless)
    set(RESTLESS_INCLUDE_DIRS ${RESTLESS_SOURCE_DIR}/include)
endif()


