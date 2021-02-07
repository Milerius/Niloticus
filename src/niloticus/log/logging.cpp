//! STD
#import <filesystem>

//! Deps
#include <date/date.h>

//! Logging
#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

//! Project Headers
#include "niloticus/base/base.hpp"
#include "niloticus/log/logging.hpp"

namespace
{
    constexpr size_t g_qsize_spdlog             = 10240;
    constexpr size_t g_spdlog_thread_count      = 2;
    constexpr size_t g_spdlog_max_file_size     = 7777777;
    constexpr size_t g_spdlog_max_file_rotation = 3;
    fs::path         g_log_path;
} // namespace

namespace details
{
    fs::path
    get_current_log_file()
    {
        using namespace std::chrono;
        using namespace date;
        static auto              timestamp = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
        static date::sys_seconds tp{seconds{timestamp}};
        static std::string       s = date::format("%Y-%m-%d-%H-%M-%S", tp);
        g_log_path                 = niloticus::get_generic_logs_folder() / (s + ".log");
        return g_log_path;
    }
} // namespace details

namespace niloticus
{
    bool
    init_logging() noexcept
    {
        //! Log Initialization
        std::string path = details::get_current_log_file().string();
        spdlog::init_thread_pool(g_qsize_spdlog, g_spdlog_thread_count);
        auto tp            = spdlog::thread_pool();
        auto stdout_sink   = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(path.c_str(), g_spdlog_max_file_size, g_spdlog_max_file_rotation);

        std::vector<spdlog::sink_ptr> sinks{stdout_sink, rotating_sink};
        auto logger = std::make_shared<spdlog::async_logger>("log_mt", sinks.begin(), sinks.end(), tp, spdlog::async_overflow_policy::block);
        spdlog::register_logger(logger);
        spdlog::set_default_logger(logger);
        spdlog::set_level(spdlog::level::trace);
        spdlog::set_pattern("[%T] [%^%l%$] [%s:%#]: %v");
        SPDLOG_INFO("Logger successfully initialized");
        return true;
    }

    fs::path
    get_log_filepath() noexcept
    {
        return g_log_path;
    }
} // namespace niloticus