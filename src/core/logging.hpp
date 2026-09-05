#pragma once

#include <utility>
#include <iostream>
#include <print>
#include <string_view>
#include <format>
#include <cassert>
#include <exception>

namespace centric::core
{
  enum class LogLevel {
    Debug,
    Info,
    Warn,
    Error,
    Fatal
  };

  template <typename... Args>
  inline void log(LogLevel level, std::format_string<Args...> fmt, Args&&... args) {
    std::string_view level_str{};
    switch (level) {
      case LogLevel::Debug: level_str = "DEBUG"; break;
      case LogLevel::Info:  level_str = "INFO"; break;
      case LogLevel::Warn:  level_str = "WARN"; break;
      case LogLevel::Error: level_str = "ERROR"; break;
      case LogLevel::Fatal: level_str = "FATAL"; break;
      default:              level_str = "UNKNOWN"; break;
    }
    auto& stream = (level == LogLevel::Error || level == LogLevel::Fatal) ? std::cerr : std::cout;
    std::print(stream, "[{}] ", level_str);
    std::println(stream, fmt, std::forward<Args>(args)...);
  }
}

#define CT_LOG(level, ...) do { centric::core::log(level,  __VA_ARGS__); } while(0)
#define CT_DEBUG(...) CT_LOG(centric::core::LogLevel::Debug, __VA_ARGS__)
#define CT_INFO(...) CT_LOG(centric::core::LogLevel::Info, __VA_ARGS__)
#define CT_WARN(...) CT_LOG(centric::core::LogLevel::Warn, __VA_ARGS__)
#define CT_ERROR(...) CT_LOG(centric::core::LogLevel::Error, __VA_ARGS__)
#define CT_FATAL(...) do { CT_LOG(centric::core::LogLevel::Fatal, __VA_ARGS__); std::terminate(); } while(0)

#define CT_ASSERT(condition) do { assert(condition); } while(0)


