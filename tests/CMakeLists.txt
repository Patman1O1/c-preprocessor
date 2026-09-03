# ── Settings ─────────────────────────────────────────────────────────────────
enable_language(CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Google Test ──────────────────────────────────────────────────────────────
include(GoogleTest)
enable_testing()

# ───────────────────────────────────────────────────────────────────────────── 
# Target: c_preprocessor_test
# Alias: c_preprocessor::c_preprocessor_test
# Type: Executable
# Dependencies: GTest::gtest_main,
#               GTest::gmock_main,
#               c_preprocessor::c_preprocessor_headers
# ─────────────────────────────────────────────────────────────────────────────
# Target definition
add_executable(c_preprocessor_test)

# Target alias
add_executable(c_preprocessor::c_preprocessor_test
    ALIAS c_preprocessor_test
)

# Target sources
target_sources(c_preprocessor_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/c_preprocessor_test.cpp
)

# Target dependencies
target_link_libraries(c_preprocessor_test
    PRIVATE
        c_preprocessor::c_preprocessor_headers
        GTest::gtest_main
        GTest::gmock_main
)

# Test discovery
gtest_discover_tests(c_preprocessor_test)
