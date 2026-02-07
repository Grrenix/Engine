#pragma once

// ===== Standard library =====
#include <algorithm>
#include <cstddef> // For std::size_t
#include <cstdint>
#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// ===== Platform =====
#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

// ===== Engine common headers =====
// Keep this small & stable!
// #include "engine/core/Assert.h"
// #include "engine/core/Log.h"
