# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 3.5)

# Declare the name of the CMake Project
project(hello_root_lib)

# if(NOT WIN32)
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
# endif()

# Find and get all the information about our package "root_lib"
find_package(root_lib REQUIRED)

get_target_property(incs root_lib::root_lib INTERFACE_INCLUDE_DIRECTORIES)

message(STATUS "\n--- hello_root_lib ---")
message(STATUS "Project_name is ${PROJECT_NAME}")
message(STATUS "root_lib found   is ${root_lib_FOUND}")
message(STATUS "root_lib include is ${incs}")

# Define an executable  target called hello_using_lib
add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)

## Link against libraries here, if required
## ...
target_link_libraries(${PROJECT_NAME} ${root_lib_LIBRARIES} root_lib::root_lib)

set(MY_STATIC_LIB_DESTINATION lib)
set(MY_SHARED_LIB_DESTINATION lib)
set(MY_BIN_DESTINATION bin)

# installation
install(TARGETS             ${PROJECT_NAME}
        DESTINATION         ${MY_BIN_DESTINATION})



