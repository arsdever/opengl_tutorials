find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)

add_executable (glapp main.cpp helper.h vertex.h shader.h shader.cpp shader_prog.h shader_prog.cpp "components/camera.hpp" "object.hpp" "prototypes.hpp" "object.cpp" "components/component.hpp" "components/transform.hpp" "components/transform.cpp" "components/mesh.hpp" "components/renderer.hpp" "components/renderer.cpp" "components/component.cpp" "components/mesh.cpp" "components/sample_meshes/triangle_mesh.hpp" "components/sample_meshes/triangle_mesh.cpp" "components/camera.hpp" "components/camera.cpp" "scene.hpp" "scene.cpp"  "timer.hpp" "timer.cpp" "fps_counter.hpp" "fps_counter.cpp" "components/input_system.hpp" "action_ctx.hpp"  "components/input_system.cpp")

target_link_libraries (glapp PUBLIC ${OpenGL_LIBRARIES} glfw glad::glad GLUT::GLUT)
target_include_directories (glapp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})