cmake_minimum_required(VERSION 3.16)
project(MyProject VERSION 1.0.0 LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable position-independent code for shared libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set the prefix path for Qt and Vulkan
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64;C:/VulkanSDK/1.3.296.0")

# Default to Release if no build type is specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
if (NOT Qt6_FOUND)
    message(FATAL_ERROR "Qt6 not found!")
endif()

# Find Vulkan
find_package(Vulkan REQUIRED)
if(NOT Vulkan_FOUND)
    message(FATAL_ERROR "Vulkan not found!")
else()
    message(STATUS "Vulkan found: ${Vulkan_INCLUDE_DIRS}")
    set(Vulkan_INCLUDE_DIRS "C:/VulkanSDK/1.3.296.0/include")
    set(Vulkan_LIBRARIES "C:/VulkanSDK/1.3.296.0/lib/vulkan-1.lib")
endif()

# Enable Qt's auto-moc, auto-rcc, and auto-uic features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Specify the path for .ui files
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/forms)

# Include directories
include_directories(include)

# Define executable target
add_executable(MyProject 
    main.cpp
    # Src
    src/MainWindow.cpp
    # include
    header/MainWindow.h
)

# Link against the Qt libraries
target_link_libraries(MyProject Qt6::Core Qt6::Widgets ${Vulkan_LIBRARIES})

# Link Vulkan include directories
target_include_directories(MyProject PRIVATE ${Vulkan_INCLUDE_DIRS})

# Configure different flags for Release and Debug
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)  # Link-time optimization
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")  # Combined flags into one line
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # Export compile commands for IDEs
endif()