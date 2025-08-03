cmake_minimum_required(VERSION 3.16)
project(JodyTamaSwitch)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Nintendo Switch SDK paths (adjust as needed)
set(NINTENDO_SDK_PATH $ENV{NINTENDO_SDK_PATH})
set(DEVKITPRO $ENV{DEVKITPRO})

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${NINTENDO_SDK_PATH}/include
    ${DEVKITPRO}/libnx/include
)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    nx
    audren
    EGL
    GLESv3
)

# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -O2
    -D__SWITCH__
)

# Copy assets to build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})