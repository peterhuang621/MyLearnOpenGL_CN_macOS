cmake_minimum_required(VERSION 3.20)
project("MyLearnOpenGL")

# APPLE flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations -Wno-unused-command-line-argument -lglfw -framework OpenGL")

# set(CMAKE_VERBOSE_MAKEFILE ON)

# set output dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# include headers
include_directories(${CMAKE_SOURCE_DIR}/includes)

# for APPLE
include_directories(/System/Library/Frameworks)
FIND_LIBRARY(COCOA_LIBRARY Cocoa)
FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
FIND_LIBRARY(IOKit_LIBRARY IOKit)
FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
SET(APPLE_LIBS ${APPLE_LIBS} ${GLFW3_LIBRARY} ${ASSIMP_LIBRARY} ${FREETYPE_LIBRARIES})
set(ALL_LIBS ${ALL_LIBS} ${APPLE_LIBS})
include_directories(/opt/homebrew/include)

# load libs
set(ALL_LIBS ${ALL_LIBS} "src/shader.cpp")
set(ALL_LIBS ${ALL_LIBS} "src/stb_image.cpp")
add_library(LIBS STATIC ${ALL_LIBS})
link_libraries(LIBS)
link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(/opt/homebrew/lib)

set(CHAPTERS
    1.getting_started

    # 2.lighting
    # 3.model_loading
    # 4.advanced_opengl
    # 5.advanced_lighting
    # 6.pbr
    # 7.in_practice
)

foreach(CHAPTER ${CHAPTERS})
    add_subdirectory(src/${CHAPTER})
endforeach(CHAPTER)
