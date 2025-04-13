# The main project is called lol.blocks
# Only MSVC, Clang and GNU compilers are supported
# Only c++ 20 is supported
# Works best using an ide that supports folder viewing (no ide specific solution files)


cmake_minimum_required(VERSION 3.18)

# main project exe
set(lol_blocks "lol.blocks.core")

# create main project
project(${lol_blocks})

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

# switch for unicode
set(UNICODE_DEFINED ON)

if(UNICODE_DEFINED)
    # define UNICODE to the compiler
    add_compile_definitions(-DUNICODE -D_UNICODE)
endif()



# main core project
file(GLOB_RECURSE cpp_source_files "../projects/lol.blocks/*.cpp")
file(GLOB_RECURSE cpp_header_files "../projects/lol.blocks/*.hpp")
file(GLOB_RECURSE lol_blocks_resources "../projects/lol.blocks/resources/*")



# creates macros for each hpp file include path
# very handy for name changes and file moves
foreach(HEADER_FILE ${cpp_header_files})
    get_filename_component(FILE_NAME ${HEADER_FILE} NAME_WE)
    set(FILE_NAME_HPP "${FILE_NAME}_hpp")
    set(HEADER_FILE_PATH "\"${HEADER_FILE}\"")
    add_compile_definitions(-D${FILE_NAME_HPP}=${HEADER_FILE_PATH})
    
    # for file name changes in the project
    # their is a file called names.hpp that manages all file name changes in the project
    if(${FILE_NAME} STREQUAL "names")
        add_compile_definitions(-DNAMES_INCLUDE=${FILE_NAME_HPP})
    endif()
endforeach()


# creates macros for each resource (full file path)
foreach(LOL_BLOCKS_RESOURCE ${lol_blocks_resources})
    # gets the name from LOL_BLOCKS_RESOURCE, LOL_BLOCKS_RESOURCE is the full path from C:
    get_filename_component(FILE_NAME ${LOL_BLOCKS_RESOURCE} NAME_WE)
    
    # gets the extension from LOL_BLOCKS_RESOURCE
    get_filename_component(FILE_EXT ${LOL_BLOCKS_RESOURCE} EXT)
    
    if(UNICODE_DEFINED AND NOT (${FILE_EXT} STREQUAL ".h" OR ${FILE_EXT} STREQUAL ".hpp"))
        # full file path in the variable LOL_BLOCKS_RESOURCE_FILE_PATH
        set(LOL_BLOCKS_RESOURCE_FILE_PATH "L\"${LOL_BLOCKS_RESOURCE}\"")
    else()
        # full file path in the variable LOL_BLOCKS_FILE_PATH
        set(LOL_BLOCKS_RESOURCE_FILE_PATH "\"${LOL_BLOCKS_RESOURCE}\"")
    endif()

    # get rid of the dot and replace it with _
    string(REPLACE "." "_" FILE_EXT ${FILE_EXT})

    # the macro name
    set(LOL_BLOCKS_RESOURCE_NAME "${FILE_NAME}${FILE_EXT}")
    
    # set the macro to the file path
    add_compile_definitions(-D${LOL_BLOCKS_RESOURCE_NAME}=${LOL_BLOCKS_RESOURCE_FILE_PATH})
endforeach()


# setup build type, define macros and exe
if(DEFINED BUILD_TYPE)
    message("Build Type: ${BUILD_TYPE}")
    if(BUILD_TYPE STREQUAL "Debug")
        add_definitions(-DDEBUG)
        add_executable(${lol_blocks} WIN32 ${cpp_source_files} ${cpp_header_files})
        target_link_libraries(${lol_blocks} PUBLIC
            d3d11
            dxgi
            d3dcompiler
        )
    elseif(BUILD_TYPE STREQUAL "Release")
        add_definitions(-DRELEASE)
        add_executable(${lol_blocks} WIN32 ${cpp_source_files} ${cpp_header_files})
        target_link_libraries(${lol_blocks} PUBLIC
            d3d11
            dxgi
            d3dcompiler
        )
    elseif(BUILD_TYPE STREQUAL "Test")
        # I use the terminal window for logging when running tests
    
        add_definitions(-DTEST)
        add_definitions(-DDEBUG)
        
        add_executable(${lol_blocks} ${cpp_source_files} ${cpp_header_files})

        # Link required Win32 libraries
        target_link_libraries(${lol_blocks} PUBLIC
            user32
            kernel32
            gdi32
            winmm
            comdlg32
            advapi32
            shell32
            ole32
            oleaut32
            d3d11
            dxgi
            d3dcompiler
        )
    endif()
endif()


