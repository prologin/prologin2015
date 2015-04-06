#include <gtest/gtest.h>

#include "../constant.hh"
#include "../errors.hh"
#include "../graph.hh"

#include "test-helpers.hh"

#include <algorithm>

// Test ordered_triple here, since it's in graph.cc

TEST(GraphTest, ordered_triple)
{
    itriple t = std::make_tuple(0,1,2);
    EXPECT_EQ(ordered_triple(0,1,2), t);
    EXPECT_EQ(ordered_triple(1,0,2), t);
    EXPECT_EQ(ordered_triple(0,2,1), t);
    EXPECT_EQ(ordered_triple(2,1,0), t);
    EXPECT_EQ(ordered_triple(1,2,0), t);
    EXPECT_EQ(ordered_triple(2,0,1), t);
}

const bool some_adj_matrix[6][6] = {
    {false, true,  false, true,  false, true},
    {true,  false, true,  true,  false, true},
    {false, true,  false, true,  false, false},
    {true,  true,  true,  false, true,  false},
    {false, false, false, true,  false, true},
    {true,  true,  false, false, true,  false}
};

// 5-----1
// |\   /|
// | \ /*|
// |  0 *| (*) diagonal from 1 to 3
// |  |* |
// |  |* |
// 4--3--2

// TODO test on larger (randomized?) graphs

Graph make_some_graph()
{
    Graph g(6);
    for (int i = 0; i < 6; ++i)
    {
        g.add_edge(i, (i+1) % 6);
    }
    g.add_edge(5,1);
    g.add_edge(0,3);
    g.add_edge(1,3);
    // redundant add_edge juste to see what it does
    g.add_edge(2,1);
    return g;
}

TEST(GraphTest, edges)
{
    Graph g = make_some_graph();
    auto edges = g.edges();

    unsigned int num_edges = 0;
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            if (some_adj_matrix[i][j])
                num_edges++;
    EXPECT_EQ(num_edges, 2*edges.size());

    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            auto e = std::make_pair(i,j);
            auto e_transpose = std::make_pair(j,i);
            // Check edge_exists()
            EXPECT_EQ(some_adj_matrix[i][j], some_adj_matrix[j][i]);
            EXPECT_EQ(some_adj_matrix[i][j], g.edge_exists(e));
            // Check edges()
            if (some_adj_matrix[i][j])
            {
                EXPECT_TRUE((std::find(edges.begin(), edges.end(), e)
                             != edges.end()) ||
                            (std::find(edges.begin(), edges.end(), e_transpose)
                             != edges.end()));
            }
            else
            {
                EXPECT_FALSE(std::find(edges.begin(), edges.end(), e)
                             != edges.end());
                EXPECT_FALSE(std::find(edges.begin(), edges.end(), e_transpose)
                             != edges.end());
            }
        }
    }
    // Note: if each edge appears at least once in the `edges` vector
    // *and* its size is the number of different edges, we know that
    // each edge appears *exactly* once
}

TEST(GraphTest, remove_incident_edges)
{
    Graph g1 = make_some_graph();
    Graph g2 = make_some_graph();

    // Delete incident edges semi-manually
    for (int u : g1.adj_list()[4])
    {
        EXPECT_TRUE(g1.edge_exists(4,u));
        g1.remove_edge(4,u);
    }
    for (int u : g1.adj_list()[3])
    {
        g1.remove_edge(3,u);
    }

    // Check number of edges deleted
    // (the correct number is determined manually by looking at the graph)
    EXPECT_EQ((int)g2.edges().size() - (int)g1.edges().size(), 5);

    // Now check remove_incident_edges
    g2.remove_incident_edges(3);
    g2.remove_incident_edges(4);
    EXPECT_EQ(g1.edges(), g2.edges());
}

TEST(GraphTest, triangles)
{
    Graph g = make_some_graph();

    auto triangles = g.triangles();

    std::map<itriple, int> triangle_count;

    for (auto& t : triangles)
    {
        // Check that the triangle actually exists
        EXPECT_TRUE(g.edge_exists(std::get<0>(t), std::get<1>(t)));
        EXPECT_TRUE(g.edge_exists(std::get<1>(t), std::get<2>(t)));
        EXPECT_TRUE(g.edge_exists(std::get<2>(t), std::get<0>(t)));

        // The list should not contain duplicates
        EXPECT_FALSE(triangle_count.find(t) != triangle_count.end());

        triangle_count[t] = 0;
    }

    for (int v = 0; v < 6; ++v)
    {
        auto incident = g.incident_triangles(v);
        for (auto& e : incident)
        {
            auto t = ordered_triple(v, e.first, e.second);
            // .at() raises an exception if the triangle doesn't exist
            // -> this serves as a verification that the triangles() method
            //    is exhaustive
            triangle_count.at(t)++;
        }
    }
    // We expect each triangle to have been counted 3 times
    for (auto& kv : triangle_count)
    {
        EXPECT_EQ(kv.second, 3);
    }

    // Now, do the same thing with triangles incident to edges
    auto edges = g.edges();
    
    for (auto& e : edges)
    {
        auto incident = g.incident_triangles(e);
        for (auto& v : incident)
        {
            auto t = ordered_triple(v, e.first, e.second);
            triangle_count.at(t)++;
        }
    }
    for (auto& kv : triangle_count)
    {
        EXPECT_EQ(kv.second, 6);
    }
}


