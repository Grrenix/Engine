#pragma once

// ===== Standard library =====
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include <algorithm>
#include <filesystem>
#include <iostream>

// ===== Platform =====
#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

// ===== Engine common headers =====
// Keep this small & stable!
// #include "engine/core/Assert.h"
// #include "engine/core/Log.h"
