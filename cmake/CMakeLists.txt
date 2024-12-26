# English explaination
# The main project is called lol.blocks.core and it is an exe
# There are two dll projects that are called lol.blocks.win32_gui and lol.blocks.dx12_gui
# Only MSVC, Clang and GNU compilers are supported
# Only c++ 20 is supported
# Works best using an ide that supports folder viewing (no ide specific solution files)


cmake_minimum_required(VERSION 3.18)

# main project exe
set(CORE_LOL_BLOCKS "lol.blocks.core")

# dll linked gui projects
set(WIN32_LOL_BLOCKS_GUI "lol.blocks.win32_gui")
set(DX12_LOL_BLOCKS_GUI "lol.blocks.dx12_gui")

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



#win32 gui lib dll include paths
set(win32gui_main_folder "../gui_projects_dll/win32_gui")
set(win32gui_base_folder "../gui_projects_dll/win32_gui/base")
set(win32gui_dependencies_folder "../gui_projects_dll/win32_gui/dependencies")

# win32 gui lib dll
file(GLOB_RECURSE win32_gui_source_files "../gui_projects_dll/win32_gui/*.cpp")
# file(GLOB_RECURSE win32_gui_header_files "../gui_projects_dll/win32_gui/*.hpp") Not needed
add_library(${WIN32_LOL_BLOCKS_GUI} SHARED ${win32_gui_source_files})
target_include_directories(${WIN32_LOL_BLOCKS_GUI} PRIVATE  ${win32gui_main_folder}
                                                            ${win32gui_base_folder} 
                                                            ${win32gui_dependencies_folder})
target_compile_features(${WIN32_LOL_BLOCKS_GUI} PRIVATE cxx_std_20)
target_compile_definitions(${WIN32_LOL_BLOCKS_GUI} PRIVATE -D PREPRO_DLL_COMPILING_WIN32_GUI_LIB)




# dx12 gui lib dll
file(GLOB_RECURSE dx12_gui_source_files "../gui_projects_dll/dx12_gui/*.cpp")
# file(GLOB_RECURSE dx12_gui_header_files "../gui_projects_dll/dx12_gui/*.hpp") Not needed
add_library(${DX12_LOL_BLOCKS_GUI} SHARED ${dx12_gui_source_files})
target_include_directories(${DX12_LOL_BLOCKS_GUI} PRIVATE "../gui_projects_dll/dx12_gui")
target_compile_features(${DX12_LOL_BLOCKS_GUI} PRIVATE cxx_std_20)
target_compile_definitions(${DX12_LOL_BLOCKS_GUI} PRIVATE -D PREPRO_DLL_COMPILING_DX12_GUI_LIB)

# main core project target includes paths
set(main_lol_blocks_exe_headers "../main_program_lol.blocks.exe/cpp_headers")
set(project_directory "..")

# main core project
add_definitions(-DUNICODE -D_UNICODE) # globaly define UNICODE
file(GLOB_RECURSE core_cpp_source_files "../main_program_lol.blocks.exe/cpp_source/*.cpp")
# file(GLOB_RECURSE core_cpp_header_files "../main_program_lol.blocks.exe/cpp_headers/*.hpp" "../main_program_lol.blocks.exe/cpp_headers/*.h") Not needed
# file(GLOB_RECURSE core_resource_files "../resources/*.rc") we will use the windows api to manage the menu bars and such!!
add_executable(${CORE_LOL_BLOCKS} WIN32 ${core_cpp_source_files})
target_include_directories(${CORE_LOL_BLOCKS} PUBLIC ${main_lol_blocks_exe_headers}
                                                     ${project_directory})
# target_include_directories(${CORE_LOL_BLOCKS} PUBLIC "../resources") we will manage this another way...
target_link_libraries(${CORE_LOL_BLOCKS} d3d12 dxgi d3dcompiler ${WIN32_LOL_BLOCKS_GUI} ${DX12_LOL_BLOCKS_GUI})
target_compile_definitions(${CORE_LOL_BLOCKS} PRIVATE -DPREPRO_USING_WIN32_GUI_LIB) # define macro for exporting win32gui lib
target_compile_definitions(${CORE_LOL_BLOCKS} PRIVATE -DPREPRO_USING_DX12_GUI_LIB) # define macro for exporting dx12 gui lib









