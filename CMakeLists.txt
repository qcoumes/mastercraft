CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(Mastercraft)

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
SET(THIRD_PARTY_PATH ${CMAKE_SOURCE_DIR}/libs)

################################### PROJECT ####################################

SET(TARGET_NAME mastercraft)
SET(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)

FILE(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.hpp)
FILE(GLOB_RECURSE SHADER_FILES ${CMAKE_SOURCE_DIR}/shader/*.glsl)

INCLUDE_DIRECTORIES(${INCLUDE_DIR})

ADD_EXECUTABLE(${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})


############################## 3RD PARTIES LIBS ################################

SET(OpenGL_GL_PREFERENCE GLVND)

# effolkronium / glm / lodepng
SET(LIBS_INCLUDE_DIR ${THIRD_PARTY_PATH}/include)

FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
ADD_SUBDIRECTORY(${THIRD_PARTY_PATH}/libcpuid)
ADD_SUBDIRECTORY(${THIRD_PARTY_PATH}/imgui)


INCLUDE_DIRECTORIES(
    SYSTEM
    ${SDL2_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${CPUID_INCLUDE_DIRS}
    ${IMGUI_INCLUDE_DIRS}
    ${LIBS_INCLUDE_DIR}
)

TARGET_LINK_LIBRARIES(
    ${TARGET_NAME}
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${CPUID_LIBRARIES}
    ${IMGUI_LIBRARIES}
)

################################### Compilation ####################################
TARGET_COMPILE_OPTIONS(
    ${TARGET_NAME} PRIVATE
    -g
    -O2
#    -Wall
#    -Wextra
#    -Wfatal-errors
    -std=c++17
)

# Adding as much warning as possible on GNU gcc/g++ and Clang
#IF (CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
#    TARGET_COMPILE_OPTIONS(
#        ${TARGET_NAME} PRIVATE
#        -Weverything
#    )
#ENDIF ()


# Disable some warnings
#TARGET_COMPILE_OPTIONS(
#    ${TARGET_NAME} PRIVATE
#    -Wno-unused-parameter
#    -Wno-switch-enum
#    -Wno-shadow
#    -Wno-exit-time-destructors
#    -Wno-c++98-compat
#    -Wno-weak-vtables
#    -Wno-padded
#)
#IF (CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
#    TARGET_COMPILE_OPTIONS(
#        ${TARGET_NAME} PRIVATE
#    )
#ENDIF ()
