cmake_minimum_required(VERSION 3.10)

set(VERSION "0.4.1")
project(cpuid LANGUAGES C CXX ASM_MASM VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

add_subdirectory(libcpuid)
add_subdirectory(cpuid_tool)

SET(CPUID_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libcpuid/ PARENT_SCOPE)
SET(CPUID_LIBRARIES cpuid PARENT_SCOPE)
