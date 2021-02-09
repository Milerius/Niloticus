#pragma once

//! STD
#include <optional>
#include <string>
#include <unordered_map>

//! Deps
#include <nlohmann/json_fwd.hpp>

//! Project Headers
#include "niloticus/base/base.hpp"
#include "niloticus/config/coins.type.hpp"

namespace niloticus
{
    struct coin_config
    {
      public:
        std::string ticker;
        std::string coinpaprika_id;
        std::string coingecko_id;
        std::string type;
        e_coin_type coin_type;
    };

    void from_json(const nlohmann::json& j, coin_config& cfg);

    using t_coins_cfg = std::unordered_map<std::string, coin_config>;

    t_coins_cfg parse_cfg(const fs::path& coins_cfg_path = fs::current_path() / "coins.cfg.json");
} // namespace niloticus