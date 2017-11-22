#include <boost/test/unit_test.hpp>

#include "fw/process.hpp"

BOOST_AUTO_TEST_CASE(should_exe_cmd) {
    const auto result = process::run("ping", "-g");

    BOOST_REQUIRE_EQUAL(result.code, 1);
}


