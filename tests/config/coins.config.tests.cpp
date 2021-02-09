//
// Created by Roman Szterg on 09/02/2021.
//

#include "doctest/doctest.h"

//! Project Headers
#include "niloticus/config/coins.config.json.hpp"

TEST_CASE("Parse coins cfg")
{
    CHECK(niloticus::parse_cfg("non_existent_cfg.json").empty());
    const auto cfg = niloticus::parse_cfg(fs::current_path() / "config_samples" / "coins.cfg.json");
    CHECK_FALSE(cfg.empty());
}