cmake_minimum_required(VERSION 2.8)

project(Biker)

find_package(OpenGL REQUIRED)
find_package(SDL 1.2 REQUIRED)

file(GLOB BikerSrc "src/*.h" "src/*.cpp")
add_executable(${PROJECT_NAME} ${BikerSrc})

set(CMAKE_CXX_FLAGS "-g")

include_directories(${OPENGL_INCLUDE_DIR}
                    ${SDL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES}
                                      ${SDL_LIBRARY})
