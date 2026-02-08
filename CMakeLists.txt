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

if(NOT SLANGC_EXECUTABLE)
    find_program(SLANGC_EXECUTABLE slangc HINTS $ENV{VULKAN_SDK}/bin)

    if(NOT SLANGC_EXECUTABLE)
        message(FATAL_ERROR "Slang compiler not found! Ensure it is installed and available in the PATH or VULKAN_SDK/bin.")
    endif()
endif()

function(add_slang_shader_target TARGET)
    cmake_parse_arguments("SHADER" "" "" "SOURCES" ${ARGN})
    set(SHADERS_DIR ${CMAKE_CURRENT_LIST_DIR}/shaders)
    set(ENTRY_POINTS -entry vertMain -entry fragMain)

    foreach(SHADER_FILE IN LISTS SHADER_SOURCES)
        get_filename_component(SHADER_DIR ${SHADER_FILE} DIRECTORY)
        get_filename_component(SHADER_NAME ${SHADER_FILE} NAME_WE)
        set(SPIRV_FILE ${SHADERS_DIR}/${SHADER_DIR}/${SHADER_NAME}.spv)

        add_custom_command(
            OUTPUT ${SPIRV_FILE}
            COMMAND ${SLANGC_EXECUTABLE} ${SHADERS_DIR}/${SHADER_FILE} -target spirv -profile spirv_1_4 -emit-spirv-directly -fvk-use-entrypoint-name ${ENTRY_POINTS} -o ${SPIRV_FILE}
            WORKING_DIRECTORY ${SHADERS_DIR}
            DEPENDS ${SHADERS_DIR}/${SHADER_FILE}
            COMMENT "Compiling Slang Shader: ${SHADER_FILE}"
            VERBATIM
        )

        list(APPEND SPIRV_FILES ${SPIRV_FILE})
    endforeach()

    add_custom_target(${TARGET} DEPENDS ${SPIRV_FILES})
endfunction()

add_slang_shader_target(shaders SOURCES triangle.slang)
add_dependencies(engine shaders)
