###########################
# Init
##########################
cmake_minimum_required(VERSION 3.5)
set(MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.cmake/Modules")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${MODULE_DIR})
include(LazyUtils)

# Generates compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(VER_MAJOR 0)
set(VER_MINOR 1)
set(VER_PATCH 0)
add_definitions(-DPR_VERSION_MAJOR=${VER_MAJOR})
add_definitions(-DPR_VERSION_MINOR=${VER_MINOR})
add_definitions(-DPR_VERSION_PATCH=${VER_PATCH})
add_definitions(-DPR_VERSION="${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}")

project(CodeCheckExe LANGUAGES CXX VERSION ${VER_MAJOR}.${VER_MINOR}.${VER_PATCH})

remove_msvc_default_warning_level()

###########################
# Compiler flags
##########################
if (WIN32)
    # The minimum runtime is Vista
    add_definitions(-D_WIN32_WINNT=0x0600)

    # Enforces WinAPI to use unicode version of functions
    add_definitions(-DUNICODE)
    add_definitions(-D_UNICODE)
endif()
###########################
# Output dir
##########################
set_output_dir("${CMAKE_BINARY_DIR}/dist")

set_msvc_flags_if("/std:c++latest /source-charset:utf-8")

###########################
# Boost
##########################
lazy_find_boost(system)

###########################
# Max compile warnings for own code only
##########################
set_msvc_flags_if("/W4")
set_gcc_flags_if("-Wall -Wextra")

###########################
# SRC
##########################
add_subdirectory("src/")

############
# Tests
############
option(UNIT_TEST "Build unit tests" OFF)
if (UNIT_TEST)
    add_subdirectory("test/")
endif()

###########################
# Linter
##########################
option(CLANG_TIDY "Enable Clang tidy checks" OFF)
if (CLANG_TIDY)
    include(ClangTidy)
    enable_clang_tidy_for(fw ai)
endif()
