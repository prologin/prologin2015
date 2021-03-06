#include "../action_ajouter_bouclier.hh"
#include "test-helpers.hh"

// All the tests below are methods coming from the ActionTest class (see
// test-helpers.hh).  This is where the "st" GameState is coming from.

// Test that player has sufficient action points for the action
TEST_F(ActionTest, ActionLier_TooFewActionPoints)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        // Move this player on an owned portal and create action
        st->set_pos(player, st->portal_pos(0));
        st->capture(0, player);
        st->capture(1, player);
        ActionLier action(st->portal_pos(1), player);

        set_points(st.get(), player, COUT_LIEN - 1);
        EXPECT_EQ(PA_INSUFFISANTS, action.check(*st));

        set_points(st.get(), player, COUT_LIEN);
        EXPECT_NE(PA_INSUFFISANTS, action.check(*st));
    }
}

// Test that the action properly behaves with an invalid position.
TEST_F(ActionTest, Deplacer_InvalidPos)
{
    ActionLier action({-1, 0}, PLAYER_1);
    st->set_pos(PLAYER_1, {0, 0});

    EXPECT_EQ(POSITION_INVALIDE, action.check(*st));
}

// Test that the action does not work when the player is not on a portal
TEST_F(ActionTest, ActionLier_NoPortalHere)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        set_points(st.get(), player, 2 * COUT_LIEN);
        st->capture(0, player);
        st->capture(1, player);
        ActionLier action(st->portal_pos(1), player);

        st->set_pos(player, {0, 0});
        EXPECT_EQ(AUCUN_PORTAIL, action.check(*st));

        st->set_pos(player, st->portal_pos(0));
        EXPECT_NE(AUCUN_PORTAIL, action.check(*st));
    }
}

// Test that the action does not work when there is no portal on the target
// destination
TEST_F(ActionTest, ActionLier_NoPortalThere)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        set_points(st.get(), player, 2 * COUT_LIEN);
        st->capture(0, player);
        st->capture(1, player);
        ActionLier action({0, 0}, player);

        st->set_pos(player, st->portal_pos(0));
        EXPECT_EQ(AUCUN_PORTAIL, action.check(*st));
    }
}

// Test that the action fails when on a neutral portal (on either endpoint)
TEST_F(ActionTest, ActionLier_NeutralPortal)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        set_points(st.get(), player, 2 * COUT_LIEN);
        st->set_pos(player, st->portal_pos(0));
        ActionLier action(st->portal_pos(1), player);

        st->neutralize(0);
        st->capture(1, player);
        EXPECT_EQ(PORTAIL_NEUTRE, action.check(*st));

        st->neutralize(1);
        st->capture(0, player);
        EXPECT_EQ(PORTAIL_NEUTRE, action.check(*st));

        st->capture(0, player);
        st->capture(1, player);
        EXPECT_NE(PORTAIL_NEUTRE, action.check(*st));
    }
}

// Test that the action fails when on an enemy portal (on either endpoint)
TEST_F(ActionTest, ActionLier_EnemyPortal)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        set_points(st.get(), player, 2 * COUT_LIEN);
        st->set_pos(player, st->portal_pos(0));
        ActionLier action(st->portal_pos(1), player);

        st->capture(0, st->get_opponent(player));
        st->capture(1, player);
        EXPECT_EQ(PORTAIL_ENNEMI, action.check(*st));

        st->capture(1, st->get_opponent(player));
        st->capture(0, player);
        EXPECT_EQ(PORTAIL_ENNEMI, action.check(*st));

        st->capture(0, player);
        st->capture(1, player);
        EXPECT_NE(PORTAIL_ENNEMI, action.check(*st));
    }
}

// Test that creating a degenerate link is impossible
TEST_F(ActionTest, ActionLier_Degenerate)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        set_points(st.get(), player, 2 * COUT_LIEN);
        st->set_pos(player, st->portal_pos(0));
        ActionLier action(st->portal_pos(0), player);

        st->capture(0, player);
        EXPECT_EQ(LIEN_DEGENERE, action.check(*st));
    }
}

// Test that creating the same link twice is impossible
TEST_F(ActionTest, ActionLier_SameLinkTwice)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        // Put the player in a correct state for creating two links
        const int initial_AP = 2 * COUT_LIEN;
        set_points(st.get(), player, initial_AP);

        st->capture(0, player);
        st->capture(1, player);
        st->set_pos(player, st->portal_pos(0));
        ActionLier action(st->portal_pos(1), player);

        // Create first link
        EXPECT_EQ(OK, action.check(*st));
        action.apply(st.get());

        // Try to create again
        EXPECT_EQ(LIEN_INTERSECTION, action.check(*st));
    }
}

// Test that creating crossing links is impossible
TEST_F(ActionTest, ActionLier_Crossing)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        const int initial_AP = 2 * COUT_LIEN;
        set_points(st.get(), player, initial_AP);

        // Create first link
        st->capture(0, player);
        st->capture(3, player);
        st->set_pos(player, st->portal_pos(0));
        ActionLier action(st->portal_pos(3), player);
        EXPECT_EQ(OK, action.check(*st));
        action.apply(st.get());

        // The player should still have enough AP to create a second link
        st->capture(1, player);
        st->capture(2, player);
        st->set_pos(player, st->portal_pos(1));
        ActionLier action2(st->portal_pos(2), player);

        // Now, it should fail
        EXPECT_EQ(LIEN_INTERSECTION, action2.check(*st));
    }
}

// Test that a regular action just does it job
TEST_F(ActionTest, ActionLier_RegularOK)
{
    for (int player : {PLAYER_1, PLAYER_2})
    {
        // Put the player in a correct state for creating a link
        const int initial_AP = COUT_LIEN + 1;
        set_points(st.get(), player, initial_AP);
        set_points(st.get(), st->get_opponent(player), initial_AP);

        st->capture(0, player);
        st->capture(1, player);
        st->set_pos(player, st->portal_pos(0));
        ActionLier action(st->portal_pos(1), player);

        EXPECT_EQ(OK, action.check(*st));
        action.apply(st.get());

        // Check that correct action points are consumed for correct player
        EXPECT_EQ(initial_AP - COUT_LIEN, st->action_points(player));
        EXPECT_EQ(initial_AP, st->action_points(st->get_opponent(player)));

        // Check that the link is created
        EXPECT_TRUE(st->graph().edge_exists({0, 1}));
        st->graph().remove_edge({0, 1});
    }
}
