project(engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(engine
    src/private/engine/pch.cpp
    src/private/engine/application/application.cpp
    src/private/engine/input/input_state.cpp
    src/private/engine/input/keyboard_map.cpp
    src/private/engine/platform/window.cpp
    src/private/engine/events/event_dispatcher.cpp
    src/private/engine/events/event_queue.cpp
    src/private/engine/events/event.cpp
    src/private/engine/events/update_event.cpp
    src/private/engine/events/input_events.cpp
    src/private/engine/events/window_events.cpp
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
