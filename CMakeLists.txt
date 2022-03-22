cmake_minimum_required (VERSION 3.13)

set (CMAKE_CXX_STANDARD 20)

add_subdirectory (events)
add_subdirectory (prof)

option (OPENGL_ENABLE_TESTING "Enable the testing of the project" ON)
project (opengl_trainings)

include ($ENV{VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)
add_subdirectory (src)

if (OPENGL_ENABLE_TESTING)
    enable_testing ()
    add_subdirectory (test)
endif (OPENGL_ENABLE_TESTING)