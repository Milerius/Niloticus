//
// Created by Roman Szterg on 08/02/2021.
//

#include "doctest/doctest.h"

#include "antara/gaming/world/world.app.hpp"
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