cmake_minimum_required(VERSION 3.10)

project(Cebeci_Engine_Shared_Library)
include("${CMAKE_CURRENT_SOURCE_DIR}/Dependencies.cmake")

file(GLOB_RECURSE core_source CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp)
file(GLOB_RECURSE render_source CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/render/*.cpp)

add_library(core SHARED ${core_source})
add_library(render SHARED ${render_source})

target_link_libraries(core PUBLIC ${dependencies_libs} render)
target_link_libraries(render PUBLIC glfw)

include_directories(
    ${dependencies_include}
    "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/render"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/render/texture"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/render/projection"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/AppManager"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/AppManager/Input"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/AppManager/TaskManager"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/AppManager/ObjectManager"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/Math"
)
