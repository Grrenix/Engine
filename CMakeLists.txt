project(engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(engine
    src/private/pch.cpp
    src/private/application/application.cpp
    src/private/input/input_state.cpp
    src/private/input/keyboard_map.cpp
    src/private/platform/window.cpp
    src/private/events/event_dispatcher.cpp
    src/private/events/event_queue.cpp
    src/private/events/event.cpp
    src/private/events/update_event.cpp
    src/private/events/input_events.cpp
    src/private/events/window_events.cpp
)

target_include_directories(engine
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/public>
)

target_precompile_headers(engine
    PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:pch.hpp>
)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(engine PUBLIC glfw)
