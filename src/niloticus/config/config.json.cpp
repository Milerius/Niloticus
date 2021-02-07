//
// Created by Roman Szterg on 07/02/2021.
//

//! STD
#include <fstream>

//! Deps
#include <nlohmann/json.hpp>

//! Project Headers
#include "niloticus/config/config.json.hpp"

namespace details
{
    void
    from_json(const nlohmann::json& j, niloticus::config& cfg)
    {
    }

    void
    to_json(nlohmann::json& j, const niloticus::config& cfg)
    {
        j["port"]     = cfg.port;
        j["hostname"] = cfg.hostname;
    }
} // namespace details

namespace niloticus
{
    config
    parse_cfg(std::error_code& ec, fs::path cfg_path, bool force_create) noexcept
    {
        config cfg;
        if (!fs::exists(cfg_path))
        {
            std::ofstream  ofs(cfg_path);
            nlohmann::json cfg_json;
            details::to_json(cfg_json, cfg);
            ofs << cfg_json.dump(4);
        }
        return cfg;
    }
} // namespace niloticus