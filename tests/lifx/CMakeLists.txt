INCLUDE_DIRECTORIES(
    ${LIGHTSD_SOURCE_DIR}/lifx/
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../core
    ${LIGHTSD_BINARY_DIR}/lifx/
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/../core
)

ADD_ALL_SUBDIRECTORIES()
