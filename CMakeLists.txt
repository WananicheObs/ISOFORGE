cmake_minimum_required(VERSION 3.20)
set_property(GLOBAL PROPERTY CXX_STANDARD 20)
set_property(GLOBAL PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)


#for the compiler
set(COMPILER ISOFORGE)
set(COMPILER_VERSION_MAJOR 0)
set(COMPILER_VERSION_MINOR 2)
project(${COMPILER} VERSION 0.1)


#------- grab all external, DOWNLOAD
find_package(Git)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    #update submodule as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()
#------- VERIFY IF DOWNLOADED
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/.external/glaze/CMakeLists.txt")
    message(FATAL_ERROR "the glaze submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please try again!!")
endif()


#add all external
add_subdirectory(.external/glaze)

file(GLOB COMPILER_SOURCES
    COMPILER/*.cpp
)
file(GLOB COMPILER_HEADERS
    COMPILER/*.h
)
add_executable(${COMPILER} ${COMPILER_SOURCES} ${COMPILER_HEADERS})
target_include_directories(${COMPILER} PUBLIC
    ${PROJECT_BINARY_DIR}
    .external/glaze/include
)
#this link in the build directory, not the ISOFORGE directory I think
target_link_directories(${COMPILER} PRIVATE 
    .external/glaze/src
)
target_link_libraries(${COMPILER}
    glaze::glaze
)

#configure files with cmake data
configure_file(ISOFORGEconfig.h.in ISOFORGEconfig.h)