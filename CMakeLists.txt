cmake_minimum_required(VERSION 3.25)
project(DalilAlassane LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "")

find_package(glfw3        CONFIG REQUIRED)
find_package(glad         CONFIG REQUIRED)
find_package(glm          CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)
find_package(imgui        CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Shader.cpp           src/Shader.hpp
    src/Camera.cpp           src/Camera.hpp
    src/ObjModel.cpp         src/ObjModel.hpp
    src/stb_impl.cpp
    src/imgui/backends/imgui_impl_glfw.cpp
    src/imgui/backends/imgui_impl_opengl3.cpp
    src/Skybox.cpp           src/Skybox.hpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/imgui
    ${CMAKE_SOURCE_DIR}/src/imgui/backends
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad::glad
    glm::glm
    tinyobjloader::tinyobjloader
    imgui::imgui
)

if (WIN32)      
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif (UNIX)    
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)

add_custom_target(show_outfile ALL
    COMMAND ${CMAKE_COMMAND} -E echo "[INFO] Built: $<TARGET_FILE:${PROJECT_NAME}>"
    DEPENDS ${PROJECT_NAME}
)
