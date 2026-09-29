cmake_minimum_required(VERSION 3.20)

project(VTX
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(VTX INTERFACE)

target_include_directories(VTX
    INTERFACE
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
)

option(VTX_BUILD_TESTS "Build tests" ON)

if(VTX_BUILD_TESTS)
    enable_testing()
    add_executable(vtx_test
        test/main.cpp
    )
    target_link_libraries(vtx_test
        PRIVATE VTX
    )
    add_test(
        NAME VTXTest
        COMMAND vtx_test
    )
endif()