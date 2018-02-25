cmake_minimum_required(VERSION 2.6)
project(ExoTest)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Locate my header files
include_directories(../include)
include_directories(../src)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(ExoTest test_node.cpp)
target_link_libraries(ExoTest ${GTEST_LIBRARIES} pthread)

# Set the standard to c++ 11
set_target_properties(ExoTest PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)