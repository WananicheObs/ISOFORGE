
#[==[
set(CMAKE_CXX_FLAGS "/utf-8")
set(CMAKE_C_FLAGS "/utf-8")

#set(CMAKE_C_COMPILER C:/msys64/mingw64/bin/gcc)
#set(CMAKE_CXX_COMPILER C:/msys64/mingw64/bin/g++)

include(Includes.cmake)

#variables
set(NAME test)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 2)

file(GLOB SOURCES 
#not build library
    includes/*/*.h
    includes/*/*.hpp
    includes/*/*.cpp
#imgui
    includes/imgui-master/*.h
    includes/imgui-master/*.cpp
    includes/imgui-master/backends/imgui_impl_sdl2.h
    includes/imgui-master/backends/imgui_impl_sdl2.cpp
    includes/imgui-master/backends/imgui_impl_vulkan.h
    includes/imgui-master/backends/imgui_impl_vulkan.cpp
#custom files
    src/*.h
    src/*.cpp
    src/*/*.h
    src/*/*.cpp
)

#project
cmake_minimum_required(VERSION 3.20)
project(${NAME} VERSION ${VERSION_MAJOR}.${VERSION_MINOR})

add_executable(${NAME} ${SOURCES})
set_property (TARGET ${NAME} PROPERTY CXX_STANDARD 20)
set_property (TARGET ${NAME} PROPERTY VS_DPI_AWARE "PerMonitor")

#configure the setting file
configure_file(src/setting.h.in setting.h)
#link the setting file
target_include_directories(${NAME} PUBLIC ${PROJECT_BINARY_DIR})

#build include into library
#[===[
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(vk_bootstrap SHARED includes/vk_bootstrap/VkBootstrap.cpp)
target_compile_features(vk_bootstrap PRIVATE cxx_std_17)
target_include_directories(vk_bootstrap PRIVATE ${Vulkan_DIRS})
set_target_properties(vk_bootstrap PROPERTIES PUBLIC_HEADER "includes/vk_bootstrap/VkBootstrap.h;includes/vk_bootstrap/VkBootstrapDispatch.h")
target_link_libraries(${NAME} PUBLIC vk_bootstrap)
]===]

#directory
target_include_directories(${NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/worldGen"
    "${PROJECT_SOURCE_DIR}/includes"
    "${PROJECT_SOURCE_DIR}/includes/imgui-master"
    "${PROJECT_SOURCE_DIR}/includes/fastgltf/include"
    ${Vulkan_DIRS}
)
add_subdirectory(includes/fastgltf EXCLUDE_FROM_ALL)
 #link library
 target_link_libraries(${NAME} PRIVATE
    #$(simdjson_LIBS)
    ${Vulkan_LIBS}
    ${SDL_LIBS}
    fastgltf
)
]==]

cmake_minimum_required(3.20)
set(COMPILER ISOFORGE)

