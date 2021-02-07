#pragma once

#ifndef SPDLOG_ACTIVE_LEVEL
#    define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif
#include <spdlog/spdlog.h>

namespace niloticus
{
    bool init_logging() noexcept;
    fs::path get_log_filepath() noexcept;
}