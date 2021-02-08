#pragma once

//! Deps
#include "antara/gaming/world/world.app.hpp"

namespace ag = antara::gaming;

namespace niloticus
{
    class worker_application : public ag::world::app
    {
      public:
        worker_application() noexcept;
        int start() noexcept;
    };
} // namespace niloticus