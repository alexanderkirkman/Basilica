cmake_minimum_required(VERSION 3.23)

# ---- Project ----
project(BasilicaWorkspace VERSION 0.1.0 LANGUAGES CXX)

# Default to Release on single-config generators (Ninja/Unix Makefiles)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Unified output dirs (bin/ and lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# For multi-config generators (Xcode/VS)
if(CMAKE_CONFIGURATION_TYPES)
  foreach(cfg IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER "${cfg}" CFG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CFG} "${CMAKE_BINARY_DIR}/bin/${cfg}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CFG} "${CMAKE_BINARY_DIR}/lib/${cfg}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CFG} "${CMAKE_BINARY_DIR}/lib/${cfg}")
  endforeach()
endif()

# Small helper for warnings
function(target_set_warnings tgt)
  if(MSVC)
    target_compile_options(${tgt} PRIVATE /W4 /permissive- /Zc:preprocessor)
  else()
    target_compile_options(${tgt} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
  endif()
endfunction()

# Optionally enable "unity"/jumbo builds later
option(BUILD_UNITY "Enable unity (jumbo) builds" OFF)

# Subprojects
add_subdirectory(Basilica)
add_subdirectory(Sandbox)
