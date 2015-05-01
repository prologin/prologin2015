#include "../actions.hh"

#include "test-helpers.hh"


// All the tests below are methods coming from the ActionTest class (see
// test-helpers.hh).  This is where the "st" GameState is coming from.

// Test that ActionCapturer rejects players that aren't on a portal.
TEST_F(ActionTest, Capturer_NoPortal)
{
    ActionCapturer act(PLAYER_1);

    EXPECT_EQ(AUCUN_PORTAIL, act.check(st));
}

// Test that ActionCapturer rejects portals that already are owned.
TEST_F(ActionTest, Capturer_PortalOwned)
{
    ActionCapturer act(PLAYER_1);

    // First assign two portals to players.
    st->capture(0, PLAYER_1);
    st->capture(1, PLAYER_2);

    // Then see if ActionCapturer accepts to take them.
    st->set_pos(PLAYER_1, st->portal_pos(0));
    EXPECT_EQ(PORTAIL_AMI, act.check(st));

    st->set_pos(PLAYER_1, st->portal_pos(1));
    EXPECT_EQ(PORTAIL_ENNEMI, act.check(st));
}

// Test that ActionCapturer rejects too few action points.
TEST_F(ActionTest, Capturer_TooFewActionPoints)
{
    ActionCapturer act(PLAYER_1);

    // First move the player on a cell that contains a portal and remove enough
    // actions point.
    st->set_pos(PLAYER_1, {1, 1});
    
    // since capture now costs 1, the following is obsolete
    // st->decrement_action_points(PLAYER_1, NB_POINTS_ACTION - 1);
    // ASSERT_TRUE(COUT_CAPTURE > 1);
    // st->decrement_action_points(PLAYER_1, NB_POINTS_ACTION);
    // EXPECT_EQ(1, st->action_points(PLAYER_1));
    // EXPECT_EQ(PA_INSUFFISANTS, act.check(st));

    // Likewise with no action point at all.
    // st->decrement_action_points(PLAYER_1, 1);
    st->decrement_action_points(PLAYER_1, NB_POINTS_ACTION);
    EXPECT_EQ(0, st->action_points(PLAYER_1));
    EXPECT_EQ(PA_INSUFFISANTS, act.check(st));
}
//
// Test that a regular successful ActionCapturer just does its job.
TEST_F(ActionTest, Capturer_RegularOK)
{
    ActionCapturer act(PLAYER_1);

    // First move the player on a cell that contains a neutral portal.
    st->set_pos(PLAYER_1, st->portal_pos(0));

    EXPECT_EQ(OK, act.check(st));
    act.apply_on(st);

    EXPECT_EQ(PLAYER_1, st->owner(0));

    // Check that actions points are updated (or not) accordingly.
    EXPECT_EQ(NB_POINTS_ACTION - COUT_CAPTURE, st->action_points(PLAYER_1));
    EXPECT_EQ(NB_POINTS_ACTION,                st->action_points(PLAYER_2));
}

// Test that action points are reset when going to the next turn.
TEST_F(ActionTest, Capturer_NextTurnResetsPoints)
{
    ActionCapturer act(PLAYER_1);

    // First move the player on a cell that contains a neutral portal and
    // remove all action points for him.
    st->set_pos(PLAYER_1, st->portal_pos(0));
    st->decrement_action_points(PLAYER_1, NB_POINTS_ACTION);
    EXPECT_EQ(0, st->action_points(PLAYER_1));
    ASSERT_EQ(PA_INSUFFISANTS, act.check(st));

    st->end_of_player_turn(PLAYER_1);
    ASSERT_EQ(OK, act.check(st));
}
