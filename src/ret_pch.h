#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <utility>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstddef>
#include "logging.h"

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

#ifdef __GNUC__
#define INLINE __attribute__((always_inline))
#elif _MSC_VER && !__INTEL_COMPILER
#define INLINE __forceinline
#endif