//
// Created by Roman Szterg on 08/02/2021.
//

//! STD
#include <sstream>

//! Deps
#include <range/v3/view.hpp>

#include "niloticus/log/logging.hpp"
#include "niloticus/services/markets/coingecko/coingecko.price.hpp"

namespace niloticus
{
    std::string
    to_coingecko_url(price_coingecko_request&& request) noexcept
    {
        std::string uri = g_base_uri_price;
        using ranges::views::ints;
        using ranges::views::zip;
        auto fill_list_functor = [](auto&& container, auto& uri) {
            for (auto&& [cur_quote, idx]: zip(container, ints(0u, ranges::unreachable)))
            {
                uri.append(cur_quote);

                //! Append only if not last element, idx start at 0, if idx + 1 == quotes.size(), we are on the last elemnt, we don't append.
                if (idx < container.size() - 1)
                {
                    uri.append(",");
                }
            }
        };

        auto fill_bool_functor = [&uri](const std::string& field_name, const std::optional<std::string>& value) {
            if (value.has_value())
            {
                uri.append(field_name);
                uri.append(value.value());
            }
        };

        fill_list_functor(request.ids, uri);
        uri.append("&vs_currencies=");
        fill_list_functor(request.currencies, uri);
        fill_bool_functor("&include_market_cap=", request.include_marketcap);
        fill_bool_functor("&include_24hr_change=", request.include_24hr_change);
        fill_bool_functor("&include_24hr_vol=", request.include_24hr_vol);
        fill_bool_functor("&include_last_updated_at=", request.include_last_updated_at);
        SPDLOG_TRACE("api::provider::coingecko::price uri: {}", uri);
        return uri;
    }
} // namespace niloticus
