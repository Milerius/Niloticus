#pragma once

//! STD
#import <filesystem>
#import <string>
#import <system_error>

namespace fs = std::filesystem;

//! Constants
namespace
{
    constexpr const char* cfg_filename = "niloticus.config.json";
}

namespace niloticus
{
    struct config
    {
        std::uint16_t port{6666};
        std::string   hostname{"localhost"};
    };

    config parse_cfg(const fs::path& cfg_path = fs::current_path() / cfg_filename, bool force_create = true) noexcept;
} // namespace niloticus
