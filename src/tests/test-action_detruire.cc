#include "../action_detruire.hh"
#include "test-helpers.hh"

// All the tests below are methods coming from the ActionTest class (see
// test-helpers.hh).  This is where the "st" GameState is coming from.

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

// Test that action fails when on a neutral portal
TEST_F(ActionTest, ActionDetruire_NeutralPortal)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        set_points(st, player, 2 * COUT_DESTRUCTION);
        st->set_pos(player, st->portal_pos(0));
        ActionDetruire action(player);

        st->capture(0, -1);
        EXPECT_EQ(PORTAIL_NEUTRE, action.check(st));

        st->capture(0, st->get_opponent(player));
        EXPECT_NE(PORTAIL_NEUTRE, action.check(st));
    }
}

// Test that a regular action just does it job
TEST_F(ActionTest, ActionDetruire_RegularOK)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        for (int shields = 0; shields < MAX_BOUCLIERS; ++shields)
        {
            // Put the player in a correct state for destroying a portal
            const int initial_AP = COUT_DESTRUCTION +
                shields * COUT_DESTRUCTION_BOUCLIER + 1;
            set_points(st, player, initial_AP);
            set_points(st, st->get_opponent(player), initial_AP);
            st->set_pos(player, st->portal_pos(0));
            st->capture(0, st->get_opponent(player));
            for (int i = 0; i < shields; ++i)
                st->add_shield(0);
            ActionDetruire action(player);

            EXPECT_EQ(OK, action.check(st));
            action.apply_on(st);

            // Check that correct action points are consumed for correct player
            EXPECT_EQ(initial_AP - COUT_DESTRUCTION -
                      shields * COUT_DESTRUCTION_BOUCLIER,
                      st->action_points(player));
            EXPECT_EQ(initial_AP, st->action_points(st->get_opponent(player)));

            // Check that portal is destroyed
            EXPECT_EQ(-1, st->owner(0));
            EXPECT_EQ(0, st->num_shields(0));
        }
    }
}
