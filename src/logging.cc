#include "logging.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace RetroEngine {
    std::shared_ptr<spdlog::logger> Logging::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Logging::s_Logger;
    
    void Logging::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("RETRO-ENGINE");
        
        s_CoreLogger->set_level(spdlog::level::trace);
        
        s_Logger = spdlog::stdout_color_mt("GAME");
        
        s_Logger->set_level(spdlog::level::trace);
    }
}