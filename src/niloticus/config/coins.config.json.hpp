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
    struct electrum_server
    {
        std::string                url;
        std::optional<std::string> protocol{"TCP"};
        std::optional<bool>        disable_cert_verification{false};
    };

    void to_json(nlohmann::json& j, const electrum_server& cfg);
    void from_json(const nlohmann::json& j, electrum_server& cfg);

    struct coin_config
    {
      public:
        static constexpr const char* erc_gas_stations = "https://ethgasstation.info/json/ethgasAPI.json";
        using electrum_servers                        = std::vector<electrum_server>;
        using eth_nodes                               = std::vector<std::string>;
        std::string                     ticker;
        std::string                     gui_ticker; ///< Ticker displayed in the gui
        std::string                     name;       ///< nice name
        std::optional<electrum_servers> electrum_urls;
        std::optional<eth_nodes>        eth_urls;
        bool                            is_claimable{false};
        std::string                     minimal_claim_amount{"0"};
        bool                            currently_enabled{false};
        bool                            active{false};
        std::string                     coinpaprika_id;
        std::string                     coingecko_id;
        bool                            is_custom_coin{false};
        std::string                     type;
        std::vector<std::string>        explorer_url; ///< usefull for transaction, take this url and append transaction id
        std::string                     tx_uri{"tx/"};
        std::string                     address_url{"address/"};
        std::optional<bool>             is_testnet{false}; ///< True if testnet (tBTC, tQTUM, QRC-20 on testnet, tETH)
        e_coin_type                     coin_type;
        bool                            checked{false};
    };

    void from_json(const nlohmann::json& j, coin_config& cfg);

    using t_coins_cfg = std::unordered_map<std::string, coin_config>;

    t_coins_cfg parse_cfg(const fs::path& coins_cfg_path = fs::current_path() / "coins.cfg.json");
} // namespace niloticus