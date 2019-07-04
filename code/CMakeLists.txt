aux_source_directory(. MAIN)
source_group("" FILES ${MAIN})

aux_source_directory(./src SRC_LIST)
source_group("src" FILES ${SRC_LIST})

file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
source_group("include" FILES ${HEADER_FILES})

file(GLOB HEADER_FILES_STB "${CMAKE_CURRENT_SOURCE_DIR}/include/stb/*.h")
source_group("include\\stb" FILES ${HEADER_FILES_STB})

include_directories(include include/stb)
add_executable(RayTracing ${SRC_LIST} ${MAIN} ${HEADER_FILES} ${HEADER_FILES_STB})