cmake_minimum_required(VERSION 3.15)
project(implicit)

set(CXX clang++)
set(CMAKE_CXX_STANDARD 20)

set(SANITIZER_FLAGS "-fsanitize=address -fsanitize=undefined")
# -fno-elide-constructors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} ${SANITIZER_FLAGS}") 

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/vector/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/src/color/include)

set(SOURCES main.cc)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/int.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logger.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rec_cnt.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graph_logger.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/color/color.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
