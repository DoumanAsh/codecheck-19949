#pragma once

#include <iostream>
#include <iterator>

#include "config.hpp"

namespace game {
    enum class Turn {
        First = 1,
        Second = 2
    };
    Turn& operator++(Turn& turn);
    const Turn operator++(const Turn& turn, int);
    std::ostream& operator<<(std::ostream& os, Turn turn);

    /**
     * Chain word game.
     *
     * Implements input iterator to provide way to access output
     * of each turn separately.
     */
    class Game {
        public:
            ///Initializes game from @ref config::Config
            explicit Game(config::Config&& config) noexcept;

            /**
             * Input iterator interface.
             */
            struct iterator {
                using difference_type = std::ptrdiff_t;
                using value_type = std::string;
                using pointer = std::string*;
                using reference = std::string&;
                using iterator_category = std::input_iterator_tag;

                iterator() noexcept = default;
                explicit iterator(Game& game) noexcept;

                const iterator& operator++();
                const iterator operator++(int);

                bool operator==(const iterator& other) const;
                bool operator!=(const iterator& other) const;

                reference operator*();

                Game* game = nullptr;
            };

            iterator begin();
            iterator end();

        private:
            config::Config data;
            bool ended = false;
            Turn turn = Turn::First;
            void end_turn() noexcept;

            std::string_view current_player() const noexcept;
            Game* process_turn();
            Game* next();
            std::string& get();
            std::string current_line;
    };
}
