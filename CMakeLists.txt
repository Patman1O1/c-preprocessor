# ── Information ──────────────────────────────────────────────────────────────
cmake_minimum_required(VERSION 4.3.0)
project("c_preprocessor"
        VERSION 0.1.0
        DESCRIPTION ""
        LANGUAGES C
)

# CMake Information
cmake_file_api(
        QUERY
        API_VERSION 1
        CODEMODEL 2.3
)

# ── Settings ─────────────────────────────────────────────────────────────────
if(PROJECT_IS_TOP_LEVEL)
    # C Settings
    set(CMAKE_C_STANDARD 23)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS OFF)
    set(CMAKE_C_VISIBILITY_PRESET hidden)
    set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    # Ensure the current source directory contains the .clang directory
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/.clang)

    # Create a symlink to compile_commands.json file
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/.clang/compile_commands.json
    )

    # Project Settings
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

    # Project Options
    option(BUILD_TESTS "Build the project's test suite" OFF)

    # Set default build type if not specified
    if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
        set_property(
            CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug"
                                                    "Release"
                                                    "MinSizeRel"
                                                    "RelWithDebInfo"
        )
    endif()
endif()

# ── Dependencies ─────────────────────────────────────────────────────────────
if(BUILD_TESTS)
    find_package(GTest REQUIRED)
endif()

include(GNUInstallDirs)

# ── Installation ─────────────────────────────────────────────────────────────
if(NOT CMAKE_SKIP_INSTALL_RULES)
    # Install headers
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
            TYPE INCLUDE)
endif()

# ─────────────────────────────────────────────────────────────────────────────
# Target: c_preprocessor_headers
# Alias: c_preprocessor::c_preprocessor_headers
# Type: Interface Library
# ───────────────────────────────────────────────────────────────────────────── 
# Target definition
add_library(c_preprocessor_headers INTERFACE)

# Target alias
add_library(c_preprocessor::c_preprocessor_headers 
    ALIAS
        c_preprocessor_headers
)

# Target headers
target_include_directories(c_preprocessor_headers
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# ─────────────────────────────────────────────────────────────────────────────
# Target: c_preprocessor
# Alias: c_preprocessor::c_preprocessor
# Type: Interface Library
# Dependencies: c_preprocessor::c_preprocessor_headers
# ─────────────────────────────────────────────────────────────────────────────
# Target definition
add_library(c_preprocessor INTERFACE)

# Target alias
add_library(c_preprocessor::c_preprocessor
    ALIAS
        c_preprocessor
)

# Target dependencies
target_link_libraries(c_preprocessor
    INTERFACE
        c_preprocessor::c_preprocessor_headers
)

# Target properties
set_target_properties(c_preprocessor PROPERTIES
        OUTPUT_NAME c_preprocessor
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        C_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
)

if(NOT CMAKE_SKIP_INSTALL_RULES)
    # Install c_preprocessor
    install(TARGETS c_preprocessor
            RUNTIME COMPONENT c_preprocessor
            LIBRARY COMPONENT c_preprocessor
            NAMELINK_COMPONENT c_preprocessor
            ARCHIVE COMPONENT c_preprocessor
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()

# ── Subdirectories ───────────────────────────────────────────────────────────
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
