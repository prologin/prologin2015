#include "../actions.hh"

#include "test-helpers.hh"


// All the tests below are methods coming from the ActionTest class (see
// test-helpers.hh).  This is where the "st" GameState is coming from.


// Test that ActionDeplacer properly behaves with an invalid position.
TEST_F(ActionTest, Deplacer_InvalidPos)
{
    ActionDeplacer act({-1, 0}, PLAYER_1);

    EXPECT_EQ(POSITION_INVALIDE, act.check(st));
}

// Test that ActionDeplacer does not accept too big moves.
TEST_F(ActionTest, Deplacer_TooBigMove)
{
    ActionDeplacer act({TAILLE_TERRAIN-1, TAILLE_TERRAIN-1}, PLAYER_1);

    EXPECT_EQ(POSITION_ELOIGNEE, act.check(st));
}

// Test that ActionDeplacer does not accept moves at all when no move point is
// left. Yes, this is probably covered by the previous test, but we never know
// what edge cases could yield!
TEST_F(ActionTest, Deplacer_NoMovePointLeft)
{
    ActionDeplacer act1({1, 1}, PLAYER_1);
    ActionDeplacer act2({0, 0}, PLAYER_1);

    // First remove all move points for player 1.
    st->increment_move_points(PLAYER_1, -NB_POINTS_DEPLACEMENT);
    EXPECT_EQ(0, st->move_points(PLAYER_1));

    // Then try to move...
    EXPECT_EQ(POSITION_ELOIGNEE, act1.check(st));
    EXPECT_EQ(0, st->move_points(PLAYER_1));

    // Actually, asking not to move is always valid!
    EXPECT_EQ(OK, act2.check(st));
    EXPECT_EQ(0, st->move_points(PLAYER_1));
}

// Test that a regular successful ActionDeplacer just does its job.
TEST_F(ActionTest, Deplacer_RegularOK)
{
    const position &new_pos = {1, 1};
    ActionDeplacer act(new_pos, PLAYER_1);

    EXPECT_EQ(OK, act.check(st));
    act.apply_on(st);

    // Check that player positions are updated (or not) accordingly.
    EXPECT_EQ(new_pos,          st->player_pos(PLAYER_1));
    EXPECT_EQ(player2_startpos, st->player_pos(PLAYER_2));

    // And check that move points are updated (or not) accordingly.
    EXPECT_EQ(NB_POINTS_DEPLACEMENT - 2, st->move_points(PLAYER_1));
    EXPECT_EQ(NB_POINTS_DEPLACEMENT,     st->move_points(PLAYER_2));
}

// Test that move points are reset when going to the next turn.
TEST_F(ActionTest, Deplacer_NextTurnResetsPoints)
{
    ActionDeplacer act({1, 1}, PLAYER_1);

    // First remove all move points for player 1.
    st->increment_move_points(PLAYER_1, -NB_POINTS_DEPLACEMENT);
    EXPECT_EQ(0, st->move_points(PLAYER_1));
    ASSERT_EQ(POSITION_ELOIGNEE, act.check(st));

    st->end_of_player_turn(PLAYER_1);
    ASSERT_EQ(OK, act.check(st));
}
