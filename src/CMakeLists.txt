find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glut REQUIRED)

add_executable (glapp main.cpp)

target_link_libraries (glapp PUBLIC glm::glm GLEW::GLEW ${OpenGL_LIBRARIES} glfw glad::glad ${GLUT_LIBRARIES})