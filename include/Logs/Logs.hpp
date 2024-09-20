#pragma once

#include "spdlog/spdlog.h"

#define VV_DEFAULT_LOGGER_NAME "VerdantValleyLogger"

#define VV_LOG(type, ...)                                                      \
  if (spdlog::get(VV_DEFAULT_LOGGER_NAME) != nullptr) {                        \
    spdlog::get(VV_DEFAULT_LOGGER_NAME)->type(__VA_ARGS__);                    \
  }

#define VV_INFO(...) VV_LOG(info, __VA_ARGS__)
#define VV_TRACE(...) VV_LOG(trace, __VA_ARGS__)
#define VV_ERROR(...) VV_LOG(error, __VA_ARGS__)
#define VV_WARN(...) VV_LOG(warn, __VA_ARGS__)
#define VV_DEBUG(...) VV_LOG(debug, __VA_ARGS__)

#define VV_ASSERT(condition, ...)                                              \
  if (!(condition)) {                                                          \
    VV_ERROR(__VA_ARGS__)                                                      \
  }
