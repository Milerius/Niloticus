#include <restinio/all.hpp>

//! Project Headers
#include "niloticus/application/server.application.hpp"
#include "niloticus/config/config.json.hpp"
#include "niloticus/log/logging.hpp"
#include "niloticus/log/server.logging.hpp"

namespace niloticus
{
    int
    server_application::run() noexcept
    {
        const auto cfg = niloticus::parse_cfg();
        using traits_t = restinio::traits_t<restinio::asio_timer_manager_t, t_spdlog_logger>;
        restinio::run(restinio::on_this_thread<traits_t>().port(cfg.port).address(cfg.hostname).request_handler([](auto req) {
            return req->create_response().set_body("Hello, World!").done();
        }));
        return 0;
    }

    server_application::server_application()
    {
        niloticus::init_logging();
    }
} // namespace niloticus