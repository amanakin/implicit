cmake_minimum_required(VERSION 3.15)
project(implicit)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "-O0  ${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined") 
set (CMAKE_LINKER_FLAGS "-O0 ${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined") 

include_directories(src/include)

set(SOURCES main.cc)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/int.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logger.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cc)

add_executable(${PROJECT_NAME} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
