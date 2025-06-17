# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.19)

project ("CMakeProject2")

add_subdirectory(Chapter01/01_CMake)

# Fetch GLFW
include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_Declare(
    vulkan
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
    GIT_TAG 1.3.296
)
FetchContent_Declare(
    taskflow
    GIT_REPOSITORY https://github.com/taskflow/taskflow.git
    GIT_TAG 3.8.0
)

# These options disable GLFW's examples, tests, and docs
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# THEN link libraries to your target
target_link_libraries(Ch01_Sample01_CMake PRIVATE glfw)