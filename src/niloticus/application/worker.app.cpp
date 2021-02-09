//! Deps
#include <restinio/all.hpp>

//! Project Headers
#include "niloticus/application/worker.app.hpp"
#include "niloticus/config/coins.config.json.hpp"
#include "niloticus/log/logging.hpp"
#include "niloticus/services/markets/coingecko/coingecko.service.hpp"

namespace niloticus
{
    worker_application::worker_application() noexcept
    {
        SPDLOG_INFO("worker_application created");
        entity_registry_.set<t_coins_cfg>(parse_cfg());
        system_manager_.create_system<coingecko_service>();
    }

    int
    worker_application::start() noexcept
    {
        SPDLOG_INFO("Starting worker microservices");
        return run();
    }
} // namespace niloticus