# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 3.0)

# Declare the name of the CMake Project
project(hello_child_lib     LANGUAGES CXX C
                            VERSION   1.0.0)

## Common CMake configuration
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

##########################################################
## ENABLE C++14 and thread
##########################################################

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

# Defines the CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_BINDIR and many other useful macros.
# See https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)

##########################################################
## Find dependencies
##########################################################

# Find and get all the information about our package "child_lib"
find_package(child_lib REQUIRED)

get_target_property(incs child_lib::child_lib INTERFACE_INCLUDE_DIRECTORIES)

message(STATUS "\n--- hello_child_lib ---")
message(STATUS "Project_name is ${PROJECT_NAME}")
message(STATUS "child_lib found   is ${child_lib_FOUND}")
message(STATUS "child_lib include is ${incs}")
message(STATUS "child_lib_LIBRARIES is ${child_lib_LIBRARIES}")

# Add the headers from "child_lib"
#include_directories(${child_lib_INCLUDE_DIRS})

# Define an executable  target called hello_using_lib
add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp)

## Link against libraries here, if required
## ...
target_link_libraries(${PROJECT_NAME} ${child_lib_LIBRARIES} child_lib::child_lib)


set(MY_STATIC_LIB_DESTINATION lib)
set(MY_SHARED_LIB_DESTINATION lib)
set(MY_BIN_DESTINATION bin)

# installation
install(TARGETS             ${PROJECT_NAME}
        DESTINATION         ${MY_BIN_DESTINATION})



