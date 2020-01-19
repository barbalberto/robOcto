# Declare the version of the CMake API for forward-compatibility
cmake_minimum_required(VERSION 3.5)

# Declare the name of the CMake Project
project(child_lib   LANGUAGES CXX C
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

#########################################################
# Find YCM repo with CMake's helper scripts
#########################################################
find_package(YCM REQUIRED)

# Defines the CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_BINDIR and many other useful macros.
# See https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html
include(GNUInstallDirs)

# from YCM, include helper functions
include(AddInstallRPATHSupport)
include(InstallBasicPackageFiles)

message(STATUS "CMAKE_INSTALL_FULL_BINDIR is ${CMAKE_INSTALL_FULL_BINDIR}")
add_install_rpath_support(BIN_DIRS "${CMAKE_INSTALL_FULL_BINDIR}"
                          LIB_DIRS "${CMAKE_INSTALL_FULL_LIBDIR}"
                          INSTALL_NAME_DIR "${CMAKE_INSTALL_FULL_LIBDIR}"
                          USE_LINK_PATH)

# Find and get all the information about our package "root_lib"
find_package(root_lib REQUIRED)
get_target_property(incs root_lib::root_lib INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "root_lib found   is ${root_lib_FOUND}")
message(STATUS "root_lib include is ${incs}")

INCLUDE_DIRECTORIES(${incs})

# List source and header files
set(LIB_SRCS  src/${PROJECT_NAME}.cpp)
set(LIB_HDRS  include/${PROJECT_NAME}/${PROJECT_NAME}.hpp)

# Define an library target called root_lib
add_library(${PROJECT_NAME} SHARED ${LIB_SRCS} ${LIB_HDRS})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PRIVATE   cxx_std_11)
                                      # INTERFACE cxx_std_11)

## Add our own include folders -- (should the include files be collected into a 'include' folder?)
target_include_directories(${PROJECT_NAME}
                            PUBLIC      $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>              # include folder, inside build
                                        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>    # include folder, after installation
                            )

# link against dependencies
target_link_libraries(${PROJECT_NAME} root_lib::root_lib)

# list headers file to be installed
set_property( TARGET    ${PROJECT_NAME}
              PROPERTY  PUBLIC_HEADER   ${LIB_HDRS})

# installation
install(TARGETS              ${PROJECT_NAME}
        EXPORT               ${PROJECT_NAME}
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

# export information to downstream packages
include(InstallBasicPackageFiles)
install_basic_package_files(${PROJECT_NAME}
                            VERSION ${${PROJECT_NAME}_VERSION}
                            COMPATIBILITY AnyNewerVersion
                            DEPENDENCIES root_lib
                            VARS_PREFIX ${PROJECT_NAME}
                            NO_CHECK_REQUIRED_COMPONENTS_MACRO)


# Add the uninstall target
include(AddUninstallTarget)
