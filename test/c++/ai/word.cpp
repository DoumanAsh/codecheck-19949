#include <boost/test/unit_test.hpp>

#include "ai/word.hpp"

BOOST_AUTO_TEST_CASE(should_return_word) {
    std::string_view current = "lolka";
    std::vector<std::string_view> available = {
        "gora",
        "autumn"
    };

    const auto result = word::choose(current, available);

    BOOST_REQUIRE(result);
    BOOST_REQUIRE(*result == available[1]);
}

BOOST_AUTO_TEST_CASE(should_not_return_word) {
    std::string_view current = "air";
    std::vector<std::string_view> available = {
        "gora",
        "autumn"
    };

    const auto result = word::choose(current, available);

    BOOST_REQUIRE(!result);
}
