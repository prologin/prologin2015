#include "../action_utiliser_turbo.hh"
#include "test-helpers.hh"

// All the tests below are methods coming from the ActionTest class (see
// test-helpers.hh).  This is where the "st" GameState is coming from.

// Test that player has sufficient action points for the action
TEST_F(ActionTest, ActionUtiliserTurbo_TooFewActionPoints)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        ActionUtiliserTurbo action(player);

        set_points(st, player, COUT_TURBO - 1);
        EXPECT_EQ(PA_INSUFFISANTS, action.check(st));

        set_points(st, player, COUT_TURBO);
        EXPECT_NE(PA_INSUFFISANTS, action.check(st));
    }
}
