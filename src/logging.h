#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

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

namespace RetroEngine {
    class Logging {
        public:
            static void Init();
            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
            inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; };
        private:
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
            static std::shared_ptr<spdlog::logger> s_Logger;
    };
}

#define RET_CORE_ERROR(...) RetroEngine::Logging::GetCoreLogger()->error(__VA_ARGS__)
#define RET_CORE_WARN(...) RetroEngine::Logging::GetCoreLogger()->warn(__VA_ARGS__)
#define RET_CORE_INFO(...) RetroEngine::Logging::GetCoreLogger()->info(__VA_ARGS__)
#define RET_CORE_TRACE(...) RetroEngine::Logging::GetCoreLogger()->trace(__VA_ARGS__)
#define RET_CORE_FATAL(...) RetroEngine::Logging::GetCoreLogger()->critical(__VA_ARGS__)

#define RET_ERROR(...) RetroEngine::Logging::GetLogger()->error(__VA_ARGS__)
#define RET_WARN(...) RetroEngine::Logging::GetLogger()->warn(__VA_ARGS__)
#define RET_INFO(...) RetroEngine::Logging::GetLogger()->info(__VA_ARGS__)
#define RET_TRACE(...) RetroEngine::Logging::GetLogger()->trace(__VA_ARGS__)
#define RET_FATAL(...) RetroEngine::Logging::GetLogger()->critical(__VA_ARGS__)