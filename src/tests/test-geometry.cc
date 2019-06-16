#include <gtest/gtest.h>

#include "../constant.hh"
#include "../errors.hh"
#include "../geometry.hh"

#include "test-helpers.hh"

// no tests for determinant/l1_distance (TODO?)

TEST(GeometryTest, segments_intersect)
{
    // Test on crossing diagonals (about 750 cases, can be reduced if too slow)

    for (int xtl = 0; xtl < 3; ++xtl)
    {
        for (int ytl = 0; ytl < 3; ++ytl)
        {
            for (int xtr = 0; xtr < 3; ++xtr)
            {
                for (int ytr = 0; ytr < 3; ++ytr)
                {
                    for (int xbl = 0; xbl < 3; ++xbl)
                    {
                        for (int ybl = 0; ybl < 3; ++ybl)
                        {
                            position tl = {xtl, ytl};
                            position tr = {10 + xtr, ytr};
                            position bl = {xbl, 10 + ybl};
                            position br = {11, 11};
                            EXPECT_TRUE(segments_intersect(tl, br, tr, bl));
                            EXPECT_TRUE(segments_intersect(tr, bl, br, tl));
                            EXPECT_FALSE(segments_intersect(tr, br, bl, tl));
                            EXPECT_FALSE(segments_intersect(tr, tl, br, bl));
                        }
                    }
                }
            }
        }
    }

    position a = {42, 0};
    position b = {0, 42};
    position c = {-42, 0};
    position d = {0, -42};
    position e = {42, 42};
    position o = {0, 0};
    position f = {21, 0};

    EXPECT_TRUE(segments_intersect(a, c, d, b));
    EXPECT_TRUE(segments_intersect(a, c, d, e));
    EXPECT_FALSE(segments_intersect(a, c, b, e));

    // cases where the segments share an endpoint
    EXPECT_FALSE(segments_intersect(a, c, c, e));
    EXPECT_FALSE(segments_intersect(a, c, a, e));

    // interior/endpoint intersection
    EXPECT_TRUE(segments_intersect(a, o, b, d));
    EXPECT_TRUE(segments_intersect(e, d, f, c));

    // Test with collinear points:
    // if P \in ]AB[, then (AP) and (PB) don't intersect according to
    // our definition, but (AP) and (AB) do
    EXPECT_FALSE(segments_intersect(a, o, c, o));
    EXPECT_TRUE(segments_intersect(a, o, c, a));
    EXPECT_TRUE(segments_intersect(a, c, c, o));

    EXPECT_FALSE(segments_intersect(d, f, e, f));
    EXPECT_TRUE(segments_intersect(d, f, e, d));
    EXPECT_TRUE(segments_intersect(d, e, e, f));

    // A non-degenerate segment should intersect itself
    EXPECT_TRUE(segments_intersect(a, b, a, b));

    position p = {3, 0};
    position q = {5, 0};
    position r = {8, 0};

    EXPECT_TRUE(segments_intersect(o, q, p, r));
    EXPECT_TRUE(segments_intersect(o, r, p, q));
    EXPECT_FALSE(segments_intersect(o, p, q, r));
}

TEST(MapTest, point_in_triangle)
{
    // positions chosen for coprimality of the vector's coordinates
    position a = {1, 0};
    position b = {0, 7};
    position c = {4, 14};

    for (int i = 2; i < 9; ++i)
    {
        position p = {1, i};
        EXPECT_TRUE(point_in_triangle(a, b, c, p));
    }
    EXPECT_FALSE(point_in_triangle(a, b, c, {0, 0}));
    EXPECT_FALSE(point_in_triangle(a, b, c, {0, 5}));
    EXPECT_FALSE(point_in_triangle(a, b, c, {2, 1}));

    // Pick's Theorem when we know there are no lattice points on the boundary

    int interior_lattice_points = 0;
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            if (point_in_triangle(a, b, c, {i, j}))
                interior_lattice_points++;
        }
    }
    EXPECT_EQ(abs(determinant(a, b, a, c)), 2 * interior_lattice_points + 1);

    // TODO test boundary points
    // (but it's not very important for the game since it's taken care of
    // by the non-crossing link condition)

    // Idea for further testing: create a version of point_in_triangle
    // which returns the barycentric coordinates as a certificate
}
