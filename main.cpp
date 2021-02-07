//! Deps
#include <restinio/all.hpp>

//! Project Headers
#include "niloticus/config/config.json.hpp"

int
main()
{
    const auto cfg = niloticus::parse_cfg();
    restinio::run(restinio::on_this_thread().port(cfg.port).address(cfg.hostname).request_handler([](auto req) {
        return req->create_response().set_body("Hello, World!").done();
    }));
    return 0;
}
