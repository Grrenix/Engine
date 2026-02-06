project(engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(engine
    src/pch.cpp
    src/engine.cpp
    src/application/application.cpp
)

target_include_directories(engine
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_precompile_headers(engine
    PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:engine/pch.h>
)
