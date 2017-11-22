#include <array>

#include <boost/test/unit_test.hpp>

#include "fw/game.hpp"
#include "fw/config.hpp"

BOOST_AUTO_TEST_CASE(should_play_game) {
    config::Config config;

    config.ai.first = "./dist/bin/ai.exe";
    config.ai.second = "./dist/bin/ai.exe";

    config.word.first = "shiritori";
    config.word.available.emplace_back("internet");
    config.word.available.emplace_back("tail");
    config.word.available.emplace_back("grep");
    config.word.available.emplace_back("less");
    config.word.available.emplace_back("telnet");
    config.word.available.emplace_back("sed");

    std::array<const char*, 5> expected_lines = {
        "FIRST (OK): internet",
        "SECOND (OK): tail",
        "FIRST (OK): less",
        "SECOND (OK): sed",
        "FIRST (NG): \nWIN - SECOND"
    };

    game::Game game(std::move(config));

    size_t idx = 0;
    for (const auto& line : game) {
        BOOST_REQUIRE(idx <= expected_lines.size());
        BOOST_REQUIRE_EQUAL(line.c_str(), expected_lines[idx]);
        ++idx;
    }
}

BOOST_AUTO_TEST_CASE(should_finish_game_on_first) {
    config::Config config;

    config.ai.first = "./dist/bin/ai.exe";
    config.ai.second = "./dist/bin/ai.exe";

    config.word.first = "shiritori";
    config.word.available.emplace_back("tail");
    config.word.available.emplace_back("grep");

    std::array<const char*, 1> expected_lines = {
        "FIRST (NG): \nWIN - SECOND"
    };

    game::Game game(std::move(config));

    size_t idx = 0;
    for (const auto& line : game) {
        BOOST_REQUIRE(idx <= expected_lines.size());
        BOOST_REQUIRE_EQUAL(line.c_str(), expected_lines[idx]);
        ++idx;
    }

}
