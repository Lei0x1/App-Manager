cmake_minimum_required(VERSION 3.16)
project(MyProject VERSION 1.0.0 LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable position-independent code for shared libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Default to Release if no build type is specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# Determine platform-specific settings
if(WIN32)
    # Windows-specific settings
    set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64;C:/VulkanSDK/1.3.296.0")
    set(CURL_INCLUDE_DIR "C:/curl-8.10.1_7-win64-mingw/include")
    set(CURL_LIBRARY "C:/curl-8.10.1_7-win64-mingw/lib/libcurl.dll.a")
    set(Vulkan_INCLUDE_DIRS "C:/VulkanSDK/1.3.296.0/include")
    set(Vulkan_LIBRARIES "C:/VulkanSDK/1.3.296.0/lib/vulkan-1.lib")

    # GUI mode for Windows
    add_executable(MyProject WIN32
        main.cpp
        src/MainWindow.cpp
        src/DownloadThread.cpp
        header/MainWindow.h
        header/DownloadThread.h
    )
elseif(APPLE)
    # macOS-specific settings
    set(CMAKE_PREFIX_PATH "/usr/local/opt/qt6")
    find_package(Vulkan REQUIRED) # macOS may require MoltenVK for Vulkan

    # GUI mode for macOS
    add_executable(MyProject
        main.cpp
        src/MainWindow.cpp
        src/DownloadThread.cpp
        header/MainWindow.h
        header/DownloadThread.h
    )
else()
    # Linux-specific settings
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(VULKAN REQUIRED vulkan)

    add_executable(MyProject
        main.cpp
        src/MainWindow.cpp
        src/DownloadThread.cpp
        header/MainWindow.h
        header/DownloadThread.h
    )
endif()

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Concurrent Network)
if (NOT Qt6_FOUND)
    message(FATAL_ERROR "Qt6 not found!")
endif()

# Find cURL
find_package(CURL REQUIRED)
if(NOT CURL_FOUND)
    message(FATAL_ERROR "cURL not found!")
endif()

# Enable Qt's auto-moc, auto-rcc, and auto-uic features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Specify the path for .ui files
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/forms)

# Include directories
include_directories(include ${CURL_INCLUDE_DIR} ${Vulkan_INCLUDE_DIRS})

# Explicitly list the files that need moc
qt6_wrap_cpp(MOC_SOURCES
    header/MainWindow.h
    header/DownloadThread.h
)

target_sources(MyProject PRIVATE
    ${MOC_SOURCES}
)

# Link libraries
target_link_libraries(MyProject Qt6::Core Qt6::Widgets Qt6::Concurrent Qt6::Network ${Vulkan_LIBRARIES} ${CURL_LIBRARY})

# Copy MainWindow.json to the output directory
add_custom_command(TARGET MyProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/src/MainWindow.json"
    $<TARGET_FILE_DIR:MyProject>
)

# Configure different flags for Release and Debug
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)  # Link-time optimization
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")  # Combined flags into one line
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # Export compile commands for IDEs
endif()