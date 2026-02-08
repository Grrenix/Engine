project(engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")

add_library(engine
    src/private/engine/pch.cpp
    src/private/engine/application/application.cpp
    src/private/engine/input/input_state.cpp
    src/private/engine/input/keyboard_map.cpp
    src/private/engine/input/mouse.cpp
    src/private/engine/platform/window.cpp
    src/private/engine/events/event_dispatcher.cpp
    src/private/engine/events/event_queue.cpp
    src/private/engine/events/event.cpp
    src/private/engine/events/update_event.cpp
    src/private/engine/events/input_events.cpp
    src/private/engine/events/window_events.cpp
    src/private/engine/graphics/renderer.cpp
)

target_include_directories(engine
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/public>
)

target_precompile_headers(engine
    PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:engine/pch.hpp>
)


set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(engine PUBLIC glfw)


set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_INSTALL OFF CACHE BOOL "" FORCE)
set(GLM_ENABLE_CXX_20 ON CACHE BOOL "" FORCE)

add_subdirectory(external/glm)
target_link_libraries(engine PUBLIC glm::glm)


find_package(Vulkan REQUIRED)
target_link_libraries(engine PUBLIC Vulkan::Vulkan)
target_compile_definitions(engine
    PRIVATE
    VULKAN_HPP_ENABLE_RAII
    VULKAN_HPP_ENABLE_EXCEPTIONS
    VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
    VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
)

if(DEFINED ENV{VULKAN_SDK})
    set(SLANG_INCLUDE_DIR "$ENV{VULKAN_SDK}/Include")
    set(SLANG_LIB_DIR "$ENV{VULKAN_SDK}/Lib")

    target_include_directories(engine
        PRIVATE
        ${SLANG_INCLUDE_DIR}
    )

    target_link_libraries(engine
        PRIVATE
        "${SLANG_LIB_DIR}/slang.lib"
    )
else()
    message(FATAL_ERROR "VULKAN_SDK environment variable not set! Cannot find Slang headers/libs.")
endif()
