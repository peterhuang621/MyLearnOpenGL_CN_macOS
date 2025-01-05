get_filename_component(FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${FOLDER_NAME})
link_libraries(assimp)
add_executable(advanced_lighting advanced_lighting.cpp)