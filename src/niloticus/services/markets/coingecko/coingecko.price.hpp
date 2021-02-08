#pragma once

#include <optional>
#include <string>
#include <vector>

namespace niloticus
{
    constexpr const char* g_base_uri_price = "https://api.coingecko.com/api/v3/simple/price?ids=";

    struct price_coingecko_request
    {
        std::vector<std::string>   ids;                 ///< eg: bitcoin,komodo
        std::vector<std::string>   currencies{{"usd"}}; ///< eg: usd,eur
        std::optional<std::string> include_marketcap;
        std::optional<std::string> include_24hr_vol;
        std::optional<std::string> include_24hr_change;
        std::optional<std::string> include_last_updated_at;
    };

    std::string to_coingecko_url(price_coingecko_request&& request) noexcept;
} // namespace niloticus

namespace niloticus::api
{
    using t_coingecko_request = price_coingecko_request;
}