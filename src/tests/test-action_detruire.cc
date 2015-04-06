#include "../action_detruire.hh"
#include "test-helpers.hh"

// All the tests below are methods coming from the ActionTest class (see
// test-helpers.hh).  This is where the "st" GameState is coming from.

// Set a given number of action points to a given player
static inline void set_points(GameState* st, int player, int pts)
{
    st->decrement_action_points(player, st->action_points(player) - pts);
}

// Test that player has sufficient action points for the action
TEST_F(ActionTest, ActionDetruire_TooFewActionPoints)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        st->set_pos(player, st->portal_pos(0));
        ActionDetruire action(player);

        for (int i = 0; i < MAX_BOUCLIERS; ++i)
        {
            st->capture(0, st->get_opponent(player));
            for (int j = 0; j < i; ++j)
                st->add_shield(0);
            set_points(st, player,
                       COUT_DESTRUCTION + COUT_DESTRUCTION_BOUCLIER * i - 1);
            EXPECT_EQ(PA_INSUFFISANTS, action.check(st));

            set_points(st, player,
                       COUT_DESTRUCTION + COUT_DESTRUCTION_BOUCLIER * i);
            EXPECT_NE(PA_INSUFFISANTS, action.check(st));
        }
    }
}
