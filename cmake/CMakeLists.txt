# The main project is called lol.blocks.core and it is an exe
# There are two dll projects that are called lol.blocks.win32_gui and lol.blocks.dx12_gui
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
set(main_lol_blocks_exe_dependencies "../projects/main_program_lol.blocks.exe/dependencies")
set(main_directory "..")
set(project_directory "../projects")
set(includes "../projects/main_program_lol.blocks.exe/dependencies/includes")



# main core project
add_definitions(-DUNICODE -D_UNICODE) # globaly define UNICODE
file(GLOB_RECURSE core_cpp_source_files "../projects/main_program_lol.blocks.exe/*.cpp" 
                                        "../projects/win32_gui/*.cpp"
                                        "../projects/win_types/*cpp"                                           
)
add_executable(${CORE_LOL_BLOCKS} WIN32 ${core_cpp_source_files})
target_include_directories(${CORE_LOL_BLOCKS} PUBLIC ${main_lol_blocks_exe_dependencies}
                                                     ${project_directory}
                                                     ${includes}
                                                     ${main_directory}
)