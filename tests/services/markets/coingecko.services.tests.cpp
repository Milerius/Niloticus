//
// Created by Roman Szterg on 08/02/2021.
//

#include "doctest/doctest.h"

//! Deps
#include "antara/gaming/world/world.app.hpp"

//! Project headers
#include "niloticus/services/markets/coingecko/coingecko.price.hpp"
#include "niloticus/services/markets/coingecko/coingecko.service.hpp"

class mock_world : protected antara::gaming::world::app
{
  public:
    mock_world()
    {
        auto& system = this->system_manager_.create_system<niloticus::coingecko_service>();
        CHECK_EQ(this->system_manager_.nb_systems(), 1);
        system.update();
    }
};

TEST_CASE("Basic coingecko system prerequisites") { mock_world world; }


TEST_CASE("coingecko price request build just with ids")
{
    niloticus::api::t_coingecko_request req{.ids = {{"bitcoin"}, {"komodo"}}};
    const auto                          result = niloticus::to_coingecko_url(std::move(req));
    CHECK_EQ(result, "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin,komodo&vs_currencies=usd");
}

TEST_CASE("coingecko price request with optional value")
{
    niloticus::api::t_coingecko_request req{.ids = {{"bitcoin"}, {"komodo"}}, .currencies = {{"usd"}, {"euro"}}, .include_last_updated_at = "true"};
    const auto                          result = niloticus::to_coingecko_url(std::move(req));
    CHECK_EQ(result, "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin,komodo&vs_currencies=usd,euro&include_last_updated_at=true");
}