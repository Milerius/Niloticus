//
// Created by Roman Szterg on 08/02/2021.
//

//! Deps
#include <doctest/doctest.h>

//! Project Headers
#include "niloticus/base/base.hpp"
#include "niloticus/log/logging.hpp"

TEST_CASE("Init logging")
{
    CHECK(niloticus::init_logging());
    CHECK(fs::exists(niloticus::get_log_filepath()));
}