#ifndef TEST_HELPERS_HH
#define TEST_HELPERS_HH

#include <sstream>

#include <gtest/gtest.h>

#include "../constant.hh"
#include "../game_state.hh"

static const position player1_startpos = {0, 0};
static const position player2_startpos = {29, 29};
static const std::string some_map = ("0 0\n"
                                     "29 29\n"
                                     "..............................\n"
                                     ".X..X.........................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     ".X..X.........................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n"
                                     "..............................\n");

class ActionTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        utils::Logger::get().level() = utils::Logger::DEBUG_LEVEL;

        std::istringstream map_stream(some_map);

        /* Create two players (no spectator).  */
        rules::Players players;
        players.add(std::make_shared<rules::Player>(0, rules::PLAYER));
        players.add(std::make_shared<rules::Player>(1, rules::PLAYER));

        st.reset(new GameState(map_stream, players));
    }

    std::unique_ptr<GameState> st;

    const int PLAYER_1 = 0;
    const int PLAYER_2 = 1;
};

// Set a given number of action points to a given player
static inline void set_points(GameState* st, int player, int pts)
{
    st->decrement_action_points(player, st->action_points(player) - pts);
}

#endif
