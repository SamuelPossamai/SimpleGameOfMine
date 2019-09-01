
#ifndef GAME_TRAITS_H
#define GAME_TRAITS_H

#include "traits.h"

class Game;

template <>
struct Traits <Game> {

    static constexpr const char *name = "SimpleGameOfMine";
    static constexpr const char *version = "v0.1.0";
    static constexpr const char *description = "Simple RPG turn-based game";
};

#endif // GAME_TRAITS_H
