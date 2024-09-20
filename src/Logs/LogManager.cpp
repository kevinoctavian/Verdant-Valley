#include "Logs/LogManager.hpp"

#include "Logs/Logs.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

#include <vector>
#include <memory>

using namespace VV;

LogManager::LogManager() {
  auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  consoleSink->set_level(spdlog::level::info);
  consoleSink->set_pattern("[VV %T] [%^%l%$] [%! %s]: %v");

  auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
      "logs/" VV_DEFAULT_LOGGER_NAME, 1024 * 1024 * 5, 3);
  fileSink->set_level(spdlog::level::debug);
  fileSink->set_pattern("[VV %T] [%l] [%! %s]: %v");

  std::vector<spdlog::sink_ptr> sinks{consoleSink, fileSink};
  auto logger = std::make_shared<spdlog::logger>(VV_DEFAULT_LOGGER_NAME,
                                                 sinks.begin(), sinks.end());
  spdlog::register_logger(logger);
  spdlog::set_default_logger(logger);
  spdlog::set_level(spdlog::level::debug);
}

LogManager::~LogManager() { spdlog::shutdown(); }
