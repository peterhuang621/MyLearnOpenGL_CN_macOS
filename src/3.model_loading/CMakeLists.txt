get_filename_component(FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${FOLDER_NAME})
add_executable(model_loadding model_loadding.cpp)
target_link_libraries(model_loadding PRIVATE ASSIMP)