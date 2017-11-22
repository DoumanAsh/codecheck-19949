#include "game.hpp"
#include "process.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

constexpr const char* PROMPT = "$";
constexpr const char* SPACE = " ";

namespace game {
    Turn& operator++(Turn& turn) {
        if (turn == Turn::Second) {
            turn = Turn::First;
        }
        else {
            using Type = typename std::underlying_type<Turn>::type;
            turn = static_cast<Turn>(static_cast<Type>(turn) + 1);
        }

        return turn;
    }

    const Turn operator++(Turn& turn, int) {
        auto result = ++turn;
        return result;
    }


    std::ostream& operator<<(std::ostream& os, Turn turn) {
        switch (turn) {
            case Turn::First: os << "FIRST"; break;
            case Turn::Second: os << "SECOND"; break;
        }

        return os;
    }
}

using namespace game;

Game::Game(config::Config&& config) noexcept : data(std::move(config)) {
    this->process_turn();
}

std::string_view Game::current_player() const noexcept {
    std::string_view result;
    switch (this->turn) {
        case Turn::First: result = this->data.ai.first; break;
        case Turn::Second: result = this->data.ai.second; break;
    }

    return result;
}

Game* Game::process_turn() {
    const auto exe_result = process::run(this->current_player().data(), this->data.word.first, this->data.word.available);

    if (exe_result.code != 0) {
        std::cerr << "Unexpected bad error code from player " << this->turn << ". Terminating...";
        exit(1);
    }

    const std::string_view last(exe_result.output.c_str());
    const auto last_in_available = std::find(this->data.word.available.begin(), this->data.word.available.end(), last);

    std::stringstream result;
    if (last_in_available == this->data.word.available.end()) {
        auto winner = this->turn;
        ++winner;
        result << this->turn << SPACE << "(NG):" << SPACE << exe_result.output << "\n"
               << "WIN" << SPACE << "-" << SPACE << winner;
        this->ended = true;
    }
    else {
        result << this->turn << SPACE << "(OK):" << SPACE << exe_result.output;

        this->data.word.first = *last_in_available;
        //Remove last element is more efficient and order doesn't really matter to us.
        std::iter_swap(last_in_available, this->data.word.available.end() - 1);
        this->data.word.available.pop_back();
    }
    this->current_line = result.str();
    ++this->turn;
    return this;
}

//Iterator accessories
Game* Game::next() {
    return this->ended ? nullptr : this->process_turn();
}

std::string& Game::get() {
    return this->current_line;
}

Game::iterator Game::begin() {
    return Game::iterator{ *this };
}

Game::iterator Game::end() {
    return Game::iterator{};
}

//Iterator interface
Game::iterator::iterator(Game& game) noexcept : game(std::addressof(game)) {}

const Game::iterator& Game::iterator::operator++() {
    game = game->next();
    return *this;
}

const Game::iterator Game::iterator::operator++(int) {
    iterator rv = *this;
    ++(*this);
    return rv;
}

bool Game::iterator::operator==(const Game::iterator& other) const {
    return game == other.game;
}

bool Game::iterator::operator!=(const Game::iterator& other) const {
    return !(*this == other);
}

Game::iterator::reference Game::iterator::operator*() {
    return game->get();
}
