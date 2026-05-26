cmake_minimum_required(VERSION 3.10)
project(VTX VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vtx
    src/Range.cpp
)
target_include_directories(vtx PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_executable(test_vtx
    tests/main.cpp
)
target_link_libraries(test_vtx
    PUBLIC
        vtx
)
