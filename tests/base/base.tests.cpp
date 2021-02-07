//
// Created by Roman Szterg on 08/02/2021.
//

//! Deps
#include <doctest/doctest.h>

//! Project Header
#include "niloticus/base/base.hpp"

TEST_CASE("get_generic_data_folder()")
{
    CHECK(fs::exists(niloticus::get_generic_data_folder()));
    CHECK(fs::exists(niloticus::get_generic_logs_folder()));
}