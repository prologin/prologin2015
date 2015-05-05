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

// Test that a regular action just does it job
TEST_F(ActionTest, ActionUtiliserTurbo_RegularOK)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        const int initial_AP = COUT_TURBO + 1;
        set_points(st, player, initial_AP);
        set_points(st, st->get_opponent(player), initial_AP);

        const int initial_MP = st->move_points(player);
        const int initial_MP_other = st->move_points(st->get_opponent(player));

        ActionUtiliserTurbo action(player);

        EXPECT_EQ(OK, action.check(st));
        action.apply_on(st);

        // Check that correct action points are consumed for correct player
        EXPECT_EQ(initial_AP - COUT_TURBO, st->action_points(player));
        EXPECT_EQ(initial_AP, st->action_points(st->get_opponent(player)));

        // Check that movement points are increased
        EXPECT_EQ(initial_MP + 1, st->move_points(player));
        EXPECT_EQ(initial_MP_other, st->move_points(st->get_opponent(player)));
    }
}
