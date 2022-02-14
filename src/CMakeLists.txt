find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glut REQUIRED)

add_executable (glapp main.cpp geometry.h triangle.h triangle.cpp helper.h vertex.h quad.h quad.cpp)

target_link_libraries (glapp PUBLIC ${OpenGL_LIBRARIES} glfw glad::glad ${GLUT_LIBRARIES})
target_include_directories (glapp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})