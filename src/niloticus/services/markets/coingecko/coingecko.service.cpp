#include "niloticus/config/coins.config.json.hpp"
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
        [[maybe_unused]] const auto& cfg = this->entity_registry_.ctx_or_set<t_coins_cfg>();
    }

    coingecko_service::~coingecko_service() noexcept
    {
        //!
        SPDLOG_INFO("coingecko_service destroyed");
    }
} // namespace niloticus