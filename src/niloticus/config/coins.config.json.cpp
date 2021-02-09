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
    to_json(nlohmann::json& j, const electrum_server& cfg)
    {
        j["url"] = cfg.url;
        if (cfg.protocol.has_value())
        {
            j["protocol"] = cfg.protocol.value();
        }
        if (cfg.disable_cert_verification.has_value())
        {
            j["disable_cert_verification"] = cfg.disable_cert_verification.value();
        }
    }

    void
    from_json(const nlohmann::json& j, electrum_server& cfg)
    {
        if (j.count("protocol") == 1)
        {
            cfg.protocol = j.at("protocol").get<std::string>();
        }
        if (j.count("disable_cert_verification") == 1)
        {
            cfg.disable_cert_verification = j.at("disable_cert_verification").get<bool>();
        }
        j.at("url").get_to(cfg.url);
    }

    void
    from_json(const nlohmann::json& j, coin_config& cfg)
    {
        j.at("coin").get_to(cfg.ticker);
        cfg.gui_ticker = j.contains("gui_coin") ? j.at("gui_coin").get<std::string>() : cfg.ticker;
        j.at("name").get_to(cfg.name);
        j.at("type").get_to(cfg.type);
        if (j.contains("electrum"))
        {
            cfg.electrum_urls = j.at("electrum").get<std::vector<electrum_server>>();
        }
        if (j.contains("eth_nodes"))
        {
            cfg.eth_urls = j.at("eth_nodes").get<std::vector<std::string>>();
        }
        cfg.is_claimable         = j.count("is_claimable") > 0;
        cfg.minimal_claim_amount = cfg.is_claimable ? j.at("minimal_claim_amount").get<std::string>() : "0";
        j.at("active").get_to(cfg.active);
        j.at("currently_enabled").get_to(cfg.currently_enabled);
        j.at("coinpaprika_id").get_to(cfg.coinpaprika_id);
        j.at("coingecko_id").get_to(cfg.coingecko_id);
        if (j.contains("is_custom_coin"))
        {
            cfg.is_custom_coin = true;
        }

        j.at("explorer_url").get_to(cfg.explorer_url);
        if (j.contains("explorer_tx_url"))
        {
            j.at("explorer_tx_url").get_to(cfg.tx_uri);
        }
        if (j.contains("explorer_address_url"))
        {
            j.at("explorer_address_url").get_to(cfg.address_url);
        }
        if (j.contains("is_testnet"))
        {
            cfg.is_testnet = j.at("is_testnet").get<bool>();
        }
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
