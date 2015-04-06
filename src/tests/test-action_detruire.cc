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

// Test that action fails when the player is not on a portal
TEST_F(ActionTest, ActionDetruire_NoPortal)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        set_points(st, player, 2 * COUT_DESTRUCTION);
        st->capture(0, st->get_opponent(player));
        ActionDetruire action(player);

        st->set_pos(player, {0, 0});
        EXPECT_EQ(AUCUN_PORTAIL, action.check(st));

        st->set_pos(player, st->portal_pos(0));
        EXPECT_NE(AUCUN_PORTAIL, action.check(st));
    }
}

// Test that action fails when on an friendly portal
TEST_F(ActionTest, ActionDetruire_FriendlyPortal)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        set_points(st, player, 2 * COUT_DESTRUCTION);
        st->set_pos(player, st->portal_pos(0));
        ActionDetruire action(player);

        st->capture(0, player);
        EXPECT_EQ(PORTAIL_AMI, action.check(st));

        st->capture(0, st->get_opponent(player));
        EXPECT_NE(PORTAIL_AMI, action.check(st));
    }
}
