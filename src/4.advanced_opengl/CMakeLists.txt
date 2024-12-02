get_filename_component(FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${FOLDER_NAME})
add_executable(depth_testing depth_testing.cpp ../shader.cpp ../stb_image.cpp)
add_executable(depth_testing_view depth_testing_view.cpp ../shader.cpp ../stb_image.cpp)