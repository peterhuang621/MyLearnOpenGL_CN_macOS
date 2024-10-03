get_filename_component(FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${FOLDER_NAME})

add_executable(color color.cpp ../shader.cpp)
add_executable(basic_lighting basic_lighting.cpp ../shader.cpp)
add_executable(material material.cpp ../shader.cpp)
add_executable(lighting_maps lighting_maps.cpp ../shader.cpp)
add_executable(light_caster light_caster.cpp ../shader.cpp)