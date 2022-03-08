find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)
find_package(libjpeg-turbo REQUIRED)

set (SOURCES
    fps_counter.cpp
    main.cpp
    object.cpp
    scene.cpp
    shader_prog.cpp
    shader.cpp
    timer.cpp

    behaviors/rotate_around_center.cpp

    components/camera.cpp
    components/component.cpp
    components/input_system.cpp
    components/light.cpp
    components/mesh.cpp
    components/renderer.cpp
    components/texture2d.cpp
    components/transform.cpp

    components/sample_meshes/stl_mesh.cpp
    components/sample_meshes/triangle_mesh.cpp
)

set (HEADERS
    action_ctx.hpp
    fps_counter.hpp
    helper.h
    object.hpp
    prototypes.hpp
    scene.hpp
    shader_prog.h
    shader.h
    stl.hpp
    timer.hpp

    behaviors/rotate_around_center.hpp

    components/camera.hpp
    components/camera.hpp
    components/component.hpp
    components/input_system.hpp
    components/light.hpp
    components/mesh.hpp
    components/renderer.hpp
    components/texture2d.hpp
    components/transform.hpp

    components/sample_meshes/stl_mesh.hpp
    components/sample_meshes/triangle_mesh.hpp

    components/vertex/descriptor.hpp
    components/vertex/normal.hpp
    components/vertex/uv_coords.hpp
    components/vertex/vertex.hpp
)

add_executable (glapp
    ${HEADERS}
    ${SOURCES}
)
set_property (TARGET glapp PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:glapp>")

target_link_libraries (glapp PUBLIC ${OpenGL_LIBRARIES} glfw glad::glad GLUT::GLUT libjpeg-turbo::turbojpeg)
target_include_directories (glapp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${JPEG_INCLUDE_DIR})