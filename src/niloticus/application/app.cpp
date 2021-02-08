//! Deps
#include <restinio/all.hpp>

//! Project Headers
#include "niloticus/application/app.hpp"
#include "niloticus/config/config.json.hpp"
#include "niloticus/log/logging.hpp"
#include "niloticus/log/server.logging.hpp"
#include "niloticus/services/markets/coingecko/coingecko.service.hpp"


struct traits_t : public restinio::default_traits_t
{
    using logger_t = niloticus::t_spdlog_logger;
};


namespace niloticus
{
    application::application() noexcept
    {
        //!
        SPDLOG_INFO("application created");
        this->system_manager_.create_system<coingecko_service>();
    }

    int
    application::start() noexcept
    {
        const auto cfg    = niloticus::parse_cfg();
        auto       server = restinio::run_async<traits_t>(
            // Asio's io_context to be used.
            // HTTP-server will use own Asio's io_context object.
            restinio::own_io_context(),
            // The settings for the HTTP-server.
            restinio::server_settings_t<traits_t>().address(cfg.hostname).port(cfg.port).request_handler([](auto req) {
                return req->create_response().set_body("Hello, World!").done();
            }),
            // The size of thread-pool for the HTTP-server.
            16);
        return this->run();
    }
} // namespace niloticus