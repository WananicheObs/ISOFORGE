cmake_minimum_required(VERSION 3.20)
set_property(GLOBAL PROPERTY CXX_STANDARD 20)
set_property(GLOBAL PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)

#for the compiler
set(COMPILER ISOFORGE)
set(COMPILER_VERSION_MAJOR 0)
set(COMPILER_VERSION_MINOR 2)
project(${COMPILER} VERSION 0.1)
file(GLOB COMPILER_SOURCES
    COMPILER/*.cpp
)
file(GLOB COMPILER_HEADERS
    COMPILER/*.h
)
add_executable(${COMPILER} ${COMPILER_SOURCES} ${COMPILER_HEADERS})
target_include_directories(${COMPILER} PUBLIC
    ${PROJECT_BINARY_DIR}
)

#configure files with cmake data
configure_file(ISOFORGEconfig.h.in ISOFORGEconfig.h)