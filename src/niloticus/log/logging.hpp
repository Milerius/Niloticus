#pragma once

#ifndef SPDLOG_ACTIVE_LEVEL
#    define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include <spdlog/spdlog.h>

#include "niloticus/base/base.hpp"

namespace niloticus
{
    bool     init_logging(const char* filename = "niloticus.server") noexcept;
    fs::path get_log_filepath() noexcept;
} // namespace niloticus