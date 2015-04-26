#include <gtest/gtest.h>

#include "../constant.hh"
#include "../errors.hh"
#include "../map.hh"

#include "test-helpers.hh"


TEST(MapTest, valid_position)
{
    Map m;

    // Test that Map::valid_position behaves properly in each corner and right
    // beyond these.

    // Beyond top-left corner
    EXPECT_TRUE(m.valid_position({0, 0}));
    EXPECT_FALSE(m.valid_position({-1, 0}));
    EXPECT_FALSE(m.valid_position({-1, -1}));
    EXPECT_FALSE(m.valid_position({0, -1}));

    // Top-right corner
    EXPECT_TRUE(m.valid_position({TAILLE_TERRAIN - 1, 0}));
    EXPECT_FALSE(m.valid_position({TAILLE_TERRAIN - 1, -1}));
    EXPECT_FALSE(m.valid_position({TAILLE_TERRAIN, -1}));
    EXPECT_FALSE(m.valid_position({TAILLE_TERRAIN, 0}));

    // Bottom-right corner
    EXPECT_FALSE(m.valid_position({TAILLE_TERRAIN, TAILLE_TERRAIN - 1}));
    EXPECT_FALSE(m.valid_position({TAILLE_TERRAIN, TAILLE_TERRAIN}));
    EXPECT_FALSE(m.valid_position({TAILLE_TERRAIN - 1, TAILLE_TERRAIN}));
    EXPECT_TRUE(m.valid_position({TAILLE_TERRAIN - 1, TAILLE_TERRAIN - 1}));

    // Bottom-left corner
    EXPECT_TRUE(m.valid_position({0, TAILLE_TERRAIN - 1}));
    EXPECT_FALSE(m.valid_position({-1, TAILLE_TERRAIN - 1}));
    EXPECT_FALSE(m.valid_position({-1, TAILLE_TERRAIN}));
    EXPECT_FALSE(m.valid_position({0, TAILLE_TERRAIN}));
}

TEST(MapTest, getters)
{
    const position invalid_pos = {0, TAILLE_TERRAIN};
    bool exception_thrown = false;
    Map m;
    std::istringstream map_stream(some_map);

    // Check invalid positions are properly handled: first for Map::is_portal,
    // then for Map::portal_id_maybe.
    try { m.is_portal(invalid_pos); }
    catch (const InvalidPosition& exc)
    {
        // Invalid positions make it raise an exception: all is fine.
        exception_thrown = true;
    }
    EXPECT_TRUE(exception_thrown);

    exception_thrown = false;
    try { m.portal_id_maybe(invalid_pos); }
    catch (const InvalidPosition& exc)
    {
        exception_thrown = true;
    }
    EXPECT_TRUE(exception_thrown);

    // Likewise for invalid players.
    exception_thrown = false;
    try { m.get_start_position(-1); }
    catch (const InvalidPlayer& exc)
    {
        exception_thrown = true;
    }
    EXPECT_TRUE(exception_thrown);


    // Now, test the getters themselves.


    // First, check with an empty map (which we have by default).
    EXPECT_FALSE(m.is_portal({1, 1}));
    EXPECT_EQ(-1, m.portal_id_maybe({1, 1}));

    const std::vector<position>& portals_empty = m.get_portals();
    EXPECT_EQ((size_t) 0, portals_empty.size());
    EXPECT_EQ(0, m.num_portals());


    // Now load our example map and check that getters behave properly.
    m.load(map_stream);

    EXPECT_TRUE(m.is_portal({1, 1}));
    // The portal IDs should be ordered in lexicographical order.
    EXPECT_EQ(0, m.portal_id_maybe({1, 1}));
    EXPECT_EQ(1, m.portal_id_maybe({1, 4}));
    EXPECT_EQ(2, m.portal_id_maybe({4, 1}));
    EXPECT_EQ(3, m.portal_id_maybe({4, 4}));

    const std::vector<position>& portals_full = m.get_portals();
    EXPECT_EQ((size_t) 4, portals_full.size());
    EXPECT_EQ(4, m.num_portals());

    EXPECT_EQ(player1_startpos, m.get_start_position(0));
    EXPECT_EQ(player2_startpos, m.get_start_position(1));
}

// TODO: it would be great testing map loading itself but the current
// implementation uses FATAL, which is not test-friendly when it comes to
// testing edge cases.
