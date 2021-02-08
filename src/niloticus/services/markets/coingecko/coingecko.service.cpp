#include "niloticus/log/logging.hpp"
#include "niloticus/services/markets/coingecko/coingecko.service.hpp"

namespace niloticus
{
    coingecko_service::coingecko_service(entt::registry& registry) : system(registry)
    {
        //!
        SPDLOG_INFO("coingecko_service created");
    }

    void
    coingecko_service::update() noexcept
    {
        //! Nothing for the moment
    }

    coingecko_service::~coingecko_service() noexcept
    {
        //!
        SPDLOG_INFO("coingecko_service destroyed");
    }
} // namespace niloticus