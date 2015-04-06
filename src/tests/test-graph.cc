#include <gtest/gtest.h>

#include "../constant.hh"
#include "../errors.hh"
#include "../graph.hh"

#include "test-helpers.hh"

#include <algorithm>

const bool some_adj_matrix[6][6] = {
    false, true,  false, true,  false, true,
    true,  false, true,  true,  false, true,
    false, true,  false, true,  false, false,
    true,  true,  true,  false, true,  false,
    false, false, false, true,  false, true,
    true,  true,  false, false, true,  false
};

// 5-----1
// |\   /|
// | \ /*|
// |  0 *| (*) diagonal from 1 to 3
// |  |* |
// |  |* |
// 4--3--2

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

    int num_edges = 0;
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
    EXPECT_EQ(g2.edges().size() - g1.edges().size(), 5);

    // Now check remove_incident_edges
    g2.remove_incident_edges(3);
    g2.remove_incident_edges(4);
    EXPECT_EQ(g1.edges(), g2.edges());
}


