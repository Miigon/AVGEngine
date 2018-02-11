cmake_minimum_required(VERSION 3.1)

project(AVGEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${AVGEngine_SOURCE_DIR}/cmake")

aux_source_directory(src SRC)
aux_source_directory(src/scene SRC_SCENE)
aux_source_directory(src/util SRC_UTIL)
add_executable(avgengine ${SRC} ${SRC_SCENE} ${SRC_UTIL})

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DAVG_LINUX)
endif()

if(UNIX)
    add_definitions(-DAVG_UNIX)
endif()

add_definitions(-DAVG_UNIVERSAL_DESKTOP)

find_package(SDL2 REQUIRED)
target_include_directories(avgengine PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(avgengine ${SDL2_LIBRARIES})

find_package(SDL2_image REQUIRED)
target_include_directories(avgengine PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(avgengine ${SDL2_IMAGE_LIBRARIES})

find_package(GLEW REQUIRED)
target_include_directories(avgengine PUBLIC ${GLEW_INCLUDE_DIRS})
target_link_libraries(avgengine ${GLEW_LIBRARIES})

find_package(OpenGL REQUIRED)
target_include_directories(avgengine PUBLIC ${OPENGL_INCLUDE_DIRS})
target_link_libraries(avgengine ${OPENGL_LIBRARIES})
