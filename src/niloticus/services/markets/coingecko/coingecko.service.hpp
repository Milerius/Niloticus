#pragma once

#include <antara/gaming/ecs/system.hpp>

namespace ag = antara::gaming;

namespace niloticus
{
    class coingecko_service final : public ag::ecs::pre_update_system<coingecko_service>
    {
      public:
        //! Constructor
        explicit coingecko_service(entt::registry& registry);

        //! Destructor
        ~coingecko_service() noexcept final;

        //! Public override
        void update() noexcept final;
    };
} // namespace niloticus

REFL_AUTO(type(niloticus::coingecko_service))