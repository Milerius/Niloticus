//! STD
#include <fstream>

//! Deps
#include <nlohmann/json.hpp>

//! Project headers
#include "niloticus/config/coins.config.json.hpp"
#include "niloticus/log/logging.hpp"


namespace niloticus
{
    void
    from_json(const nlohmann::json& j, coin_config& cfg)
    {
        j.at("coin").get_to(cfg.ticker);
        j.at("type").get_to(cfg.type);
        j.at("coinpaprika_id").get_to(cfg.coinpaprika_id);
        j.at("coingecko_id").get_to(cfg.coingecko_id);
        if (cfg.type == "QRC-20")
        {
            cfg.coin_type = e_coin_type::QRC20;
        }
        else if (cfg.type == "ERC-20")
        {
            cfg.coin_type = e_coin_type::ERC20;
        }
        else if (cfg.type == "UTXO")
        {
            cfg.coin_type = e_coin_type::UTXO;
        }
        else if (cfg.type == "Smart Chain")
        {
            cfg.coin_type = e_coin_type::SmartChain;
        }
    }

    t_coins_cfg
    parse_cfg(const fs::path& coins_cfg_path)
    {
        SPDLOG_INFO("Parsing cfg {}", coins_cfg_path.string());
        t_coins_cfg out;

        if (fs::exists(coins_cfg_path))
        {
            std::ifstream ifs(coins_cfg_path);
            assert(ifs.is_open());
            nlohmann::json config_json_data;
            ifs >> config_json_data;
            SPDLOG_INFO("Reserve {} size for coins cfg", config_json_data.size());
            out.reserve(config_json_data.size());
            out = config_json_data.get<t_coins_cfg>();
        }
        return out;
    }
} // namespace niloticus
