# The main project is called lol.blocks.core and it is an exe
# Only MSVC, Clang and GNU compilers are supported
# Only c++ 20 is supported
# Works best using an ide that supports folder viewing (no ide specific solution files)


cmake_minimum_required(VERSION 3.18)

# main project exe
set(CORE_LOL_BLOCKS "lol.blocks.core")

# create main project
project(${CORE_LOL_BLOCKS})

# We only support c++ 20 in lol.blocks
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# We only support MSVC, Clang, and GNU compilers.
set(MSVC_compiler_id "MSVC")
set(CLANG_compiler_id "Clang")
set(GCC_compiler_id "GNU")

set(is_using_MSVC_compiler OFF)
set(is_using_CLANG_compiler OFF)
set(is_using_GCC_compiler OFF)

string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} ${MSVC_compiler_id} is_using_MSVC_compiler)
string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} ${CLANG_compiler_id} is_using_CLANG_compiler)
string(COMPARE EQUAL ${CMAKE_CXX_COMPILER_ID} ${GCC_compiler_id} is_using_GCC_compiler)

if(NOT (is_using_MSVC_compiler OR is_using_CLANG_compiler OR is_using_GCC_compiler))
    message(FATAL_ERROR "Compiler not supported, You are using: ${CMAKE_CXX_COMPILER_ID}")
endif()

# this is primarly for using cmake in within an ide enviroment
# in an Open folder config, otherwise cmake will generate an ide specific solution
# that usually defines these macros anyway
if(DEFINED BUILD_TYPE)
    message("Build Type: ${BUILD_TYPE}")
    if(BUILD_TYPE STREQUAL "Debug")
        add_definitions(-DDEBUG)
    elseif(BUILD_TYPE STREQUAL "Release")
        add_definitions(-DRELEASE) 
    endif()
endif()


# main core project target includes paths
set(project_directory "../projects")




# main core project
add_definitions(-DUNICODE -D_UNICODE) # globaly define UNICODE
file(GLOB_RECURSE core_cpp_source_files "../projects/main_program_lol.blocks.exe/*.cpp")
file(GLOB_RECURSE core_cpp_header_files "../projects/main_program_lol.blocks.exe/*.hpp")
add_executable(${CORE_LOL_BLOCKS} WIN32 ${core_cpp_source_files} ${core_cpp_header_files})
target_include_directories(${CORE_LOL_BLOCKS} PUBLIC ${project_directory})
target_link_libraries(${CORE_LOL_BLOCKS} PUBLIC d3d11 dxgi d3dcompiler)

set(shader_dir "${CMAKE_SOURCE_DIR}/../projects/main_program_lol.blocks.exe/shaders")

add_custom_command(
    TARGET ${CORE_LOL_BLOCKS} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${shader_dir} ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Copying shaders to the build directory"
)

