cmake_minimum_required(VERSION 3.0.0)
project(hw03 VERSION 0.1.0)

if (MSVC)
  string(REGEX REPLACE "/W[0-9]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif (MSVC)


include(CTest)
enable_testing()

add_executable(hw03 main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES    CXX_STANDARD 17
                                                    CXX_STANDARD_REQUIRED ON
                                                    CXX_EXTENSIONS OFF)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


target_compile_options(${PROJECT_NAME} PRIVATE $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra -pedantic>
$<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->)
