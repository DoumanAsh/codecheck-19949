#include <iostream>

#include "cli.hpp"
#include "config.hpp"
#include "game.hpp"

inline static config::Config initialize(int argc, char *argv[]) {
    auto parse_result = cli::parse(argc, argv);
    if (auto error = std::get_if<std::string>(&parse_result)) {
        std::cout << *error << "\n";
        exit(1);
    }
    auto args = std::get<cli::Args>(parse_result);

    auto config_result = config::create(std::move(args));
    if (auto error = std::get_if<std::string>(&config_result)) {
        std::cout << *error << "\n";
        exit(1);
    }
    return std::get<config::Config>(config_result);
}

int main(int argc, char *argv[]) {
    game::Game game(initialize(argc, argv));

    for (const auto& line : game) {
        std::cout << line << "\n";
    }

    return 0;
}
