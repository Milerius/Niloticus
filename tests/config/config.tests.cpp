//
// Created by Roman Szterg on 07/02/2021.
//

//! Deps
#include <doctest/doctest.h>

//! Projet Headers
#include "niloticus/config/config.json.hpp"

TEST_SUITE("config tests suite")
{
    TEST_CASE("cfg create if doesn't exist")
    {
        std::error_code ec;
        const auto      cfg = niloticus::parse_cfg(ec);
        CHECK(!ec);
        CHECK_EQ(cfg.hostname, "localhost");
        CHECK_EQ(cfg.port, 6666);
        const auto supposed_cfg_path = fs::current_path() / cfg_filename;
        CHECK(fs::exists(supposed_cfg_path));
        fs::remove(supposed_cfg_path, ec);
        CHECK(!ec);
    }
}