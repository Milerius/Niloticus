//
// Created by Roman Szterg on 07/02/2021.
//

//! STD
#import <fstream>

//! Deps
#include <nlohmann/json.hpp>

//! Project Headers
#include "niloticus/config/config.json.hpp"

namespace details
{
    void
    from_json(const nlohmann::json& j, niloticus::config& cfg)
    {
        j.at("port").get_to(cfg.port);
        j.at("hostname").get_to(cfg.hostname);
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
    parse_cfg(const fs::path& cfg_path, bool force_create) noexcept
    {
        config         cfg;
        nlohmann::json cfg_json;

        if (!fs::exists(cfg_path)) ///< //! File doesn't exist let's create it
        {
            if (force_create)
            {
                std::ofstream ofs(cfg_path);

                details::to_json(cfg_json, cfg);
                ofs << cfg_json.dump(4);
            }
        }
        else
        {
            std::ifstream ifs(cfg_path);
            cfg_json = nlohmann::json::parse(ifs);
            details::from_json(cfg_json, cfg);
        }
        return cfg;
    }
} // namespace niloticus