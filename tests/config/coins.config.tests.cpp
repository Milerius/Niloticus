//
// Created by Roman Szterg on 09/02/2021.
//

#include "doctest/doctest.h"

//! Project Headers
#include "niloticus/config/coins.config.json.hpp"

TEST_CASE("Parse coins cfg")
{
    CHECK(niloticus::parse_cfg().empty());
    CHECK_FALSE(niloticus::parse_cfg(fs::current_path() / "config_samples" / "coins.cfg.json").empty());
}