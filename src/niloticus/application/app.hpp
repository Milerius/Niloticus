#pragma once

//! Deps
#include "antara/gaming/world/world.app.hpp"

namespace ag = antara::gaming;

namespace niloticus
{
    class application : public ag::world::app
    {
        //! Contructor
      public:
        application() noexcept;
        int start() noexcept;
    };
} // namespace niloticus