#define _SCL_SECURE_NO_WARNINGS
#pragma warning(push)
#pragma warning(disable : 4244)
#include <boost/process.hpp>
#pragma warning(pop)
#include <system_error>
#undef _SCL_SECURE_NO_WARNINGS
namespace bp = boost::process;
#include <vector>
#include <string>

#include "process.hpp"

using namespace process;

Result process::run(const char* cmd, const char* args) noexcept {
    std::error_code ec;
    bp::ipstream is;

    int code = bp::system(bp::search_path(cmd), args, bp::std_out > is, ec);
    std::string output(std::istreambuf_iterator<char>(is), {});

    return Result {
        code,
        output
    };
}

Result process::run(const char* cmd, std::string_view first, const std::vector<std::string_view>& words) noexcept {
    std::vector<std::string> args;
    args.emplace_back(first);
    for (const auto& word: words) {
        args.emplace_back(word);
    }

    std::error_code ec;
    bp::ipstream is;

    int code = bp::system(bp::search_path(cmd), args, bp::std_out > is, ec);
    std::string output(std::istreambuf_iterator<char>(is), {});

    return Result {
        code,
        output
    };
}
