//
// Created by Roman Szterg on 07/02/2021.
//

//! STD
#include <fstream>

//! Deps
#include <doctest/doctest.h>
#include <nlohmann/json.hpp>

//! Projet Headers
#include "niloticus/config/config.json.hpp"

SCENARIO("cfg parsing")
{
    niloticus::config cfg;
    const auto        supposed_cfg_path = fs::current_path() / cfg_filename;

    auto common_test_functor = [](auto&& cfg) {
        CHECK_EQ(cfg.hostname, "localhost");
        CHECK_EQ(cfg.port, 6666);
    };

    auto common_file_creation_functor = [supposed_cfg_path]() {
        nlohmann::json j = R"(
                          {
                            "hostname": "foo",
                            "port": 3377
                          }
                            )"_json;
        std::ofstream  ofs(supposed_cfg_path);
        ofs << j.dump(4);
    };

    auto common_file_remove_functor = [supposed_cfg_path]() {
        std::error_code ec;
        fs::remove(supposed_cfg_path, ec);
        CHECK(!ec);
    };

    common_file_remove_functor();

    WHEN("I parse a cfg that does'nt exist without default creation")
    {
        cfg = niloticus::parse_cfg(fs::current_path() / cfg_filename, false);

        THEN("I Expect the file to not be CREATED but have a default cfg values")
        {
            common_test_functor(cfg);
            CHECK_FALSE(fs::exists(supposed_cfg_path));
        }
    }

    WHEN("I parse a cfg that does'nt exist with default creation")
    {
        cfg = niloticus::parse_cfg();
        THEN("I Expect the file to not be CREATED but have a default cfg values")
        {
            common_test_functor(cfg);
            CHECK(fs::exists(supposed_cfg_path));
        }
    }

    //! Corrupt value
    WHEN("I parse a cfg that exist")
    {
        //!
        common_file_creation_functor();
        cfg = niloticus::parse_cfg();
        CHECK_EQ(cfg.hostname, "foo");
        CHECK_EQ(cfg.port, 3377);
        common_file_remove_functor();
    }
}