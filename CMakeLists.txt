cmake_minimum_required(VERSION 3.22)
project(libstc42 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723    # tag v1.17.0
        GIT_PROGRESS ON
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_library(stc42 INTERFACE)
target_include_directories(stc42 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE TESTS_SRCS LIST_DIRECTORIES false CONFIGURE_DEPENDS test/src/*.cpp)
add_executable(stc42_tests ${TESTS_SRCS})
target_link_libraries(stc42_tests
        PRIVATE stc42
        PRIVATE GTest::gtest_main
)
gtest_discover_tests(stc42_tests)
