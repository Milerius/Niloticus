#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

//! Deps
#include <nlohmann/json_fwd.hpp>

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

    struct coingecko_single_price_answer
    {
        std::string                price_in_usd;    ///< This field is guarantee to be present
        std::optional<std::size_t> last_updated_at; ///< Optional timestamp if in request include_last_updated_at is set to true
    };

    void from_json(const nlohmann::json& json_answer, coingecko_single_price_answer& answer);

    struct price_coingecko_answer
    {
        std::unordered_map<std::string, coingecko_single_price_answer> result;
    };

    std::string to_coingecko_url(price_coingecko_request&& request) noexcept;
} // namespace niloticus

namespace niloticus::api
{
    using t_coingecko_request = price_coingecko_request;
}