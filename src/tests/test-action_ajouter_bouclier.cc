#include "../action_ajouter_bouclier.hh"
#include "test-helpers.hh"

// All the tests below are methods coming from the ActionTest class (see
// test-helpers.hh).  This is where the "st" GameState is coming from.

// Set a given number of action points to a given player
static inline void set_points(GameState* st, int player, int pts)
{
    st->decrement_action_points(player, st->action_points(player) - pts);
}

// Test that player has sufficient action points for the action
TEST_F(ActionTest, ActionAjouterBouclier_TooFewActionPoints)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        // Move this player on an owned portal and create action
        st->set_pos(player, st->portal_pos(0));
        st->capture(0, player);
        ActionAjouterBouclier action(player);

        set_points(st, player, COUT_BOUCLIER - 1);
        EXPECT_EQ(PA_INSUFFISANTS, action.check(st));

        set_points(st, player, COUT_BOUCLIER);
        EXPECT_NE(PA_INSUFFISANTS, action.check(st));
    }
}

// Test that action do not work when the player is not on a portal
TEST_F(ActionTest, ActionAjouterBouclier_NoPortal)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        set_points(st, player, 2 * COUT_BOUCLIER);
        st->capture(0, player);
        ActionAjouterBouclier action(player);

        st->set_pos(player, {0, 0});
        EXPECT_EQ(AUCUN_PORTAIL, action.check(st));

        st->set_pos(player, st->portal_pos(0));
        EXPECT_NE(AUCUN_PORTAIL, action.check(st));
    }
}

// Test that action fails when on a neutral portal
TEST_F(ActionTest, ActionAjouterBouclier_NeutralPortal)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        set_points(st, player, 2 * COUT_BOUCLIER);
        st->set_pos(player, st->portal_pos(0));
        ActionAjouterBouclier action(player);

        st->capture(0, -1);
        EXPECT_EQ(PORTAIL_NEUTRE, action.check(st));

        st->capture(0, player);
        EXPECT_NE(PORTAIL_NEUTRE, action.check(st));
    }
}

// Test that action fails when on an ennemi portal
TEST_F(ActionTest, ActionAjouterBouclier_EnnemiPortal)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        set_points(st, player, 2 * COUT_BOUCLIER);
        st->set_pos(player, st->portal_pos(0));
        ActionAjouterBouclier action(player);

        st->capture(0, st->get_opponent(player));
        EXPECT_EQ(PORTAIL_ENNEMI, action.check(st));

        st->capture(0, player);
        EXPECT_NE(PORTAIL_ENNEMI, action.check(st));
    }
}
