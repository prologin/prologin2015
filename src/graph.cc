#include <algorithm>

#include "graph.hh"

Graph::Graph(int size)
    : adj_list_(size)
{
}

Graph(const Graph& g)
    : adj_list_(g.adj_list_)
{
}


bool Graph::edge_exists(ipair e) const
{
    auto s = adj_list_[e.first];
    return s.find(x) != s.end(); // lolSTL lawlSTL LOLSTL
}

void Graph::add_edge(ipair e)
{
    adj_list_[e.first].insert(e.second);
    adj_list_[e.second].insert(e.first);
}

void Graph::remove_edge(ipair e)
{
    adj_list_[e.first].erase(e.second);
    adj_list_[e.second].erase(e.first);
}

void Graph::remove_incident_edges(int v)
{
    for (int u : adj_list_[v])
    {
        adj_list_[u].erase(v);
    }
    adj_list_[v].clear();
}

std::vector<ipair> Graph::edges() const
{
    std::vector<ipair> edges;
    for (int i = 0; i < adj_list_.size(); ++i)
    {
        auto neighb = adj_list_[i];
        // Trick to eliminate duplicates: iterate only on elements higher than i
        // Consequence: the vertices of an edge are given in order
        for (auto p = neigh.upper_bound(i); p != neighb.end(); ++p)
        {
            edges.push_back(std::make_pair(i, *p));
        }
    }
}

// For planar graphs, this algorithm is *linear* in the number of edges!
// (actually, with this implementation, it's more like O(n log n))
// Reference: "Arboricity and subgraph listing algorithms",
//            Chiba & Nishizeki, 1985, SIAM. J. Comput.
std::vector<itriple> Graph::triangles() const
{
    std::vector<int> degree_order(adj_list_.size(), 0);
    for (int i = 0; i < adj_list_.size(); ++i)
    {
        degree_order[i] = i;
    }
    std::sort(degree_order.begin(), degree_order.end(),
              [this](int u, int v)
              { return adj_list_[u].size() > adj_list_[v].size() });

    std::vector<itriple> triangles;
    for (int v : degree_order)
    {
        auto neighb_v = adj_list_[v]
        for (int u : neighb_v)
        {
            auto neighb_u = adj_list_[u];

            // Ensures no duplication, and also crucial for the complexity
            neighb_u.erase(v);

            for (int w : neighb_u)
            {
                if (neighb_v.find(w) != neighb_v.end())
                {
                    // TODO Ensure lexicographic order?
                    triangles.push_back(std::make_tuple(u, v, w));
                }
            }
        }
    }

    // Repair the destructive updates
    for (int i = degree_order.size() - 1; i >= 0; --i)
    {
        int v = degree_order[i];
        for (int u : adj_list_[v])
        {
            adj_list_[u].insert(v);
        }
    }

    return triangles;
}

// Inspired by, but cannot be used as a subroutine by,
// the previous algorithm: deleted edges need to stay deleted
// until the very end to ensure good performance.
std::vector<ipair> Graph::incident_triangles(int v) const
{
    std::vector<ipair> triangles;

    auto neighb_v = adj_list_[v];
    for (int u : neighb_v)
    {
        auto neighb_u = adj_list_[u];
        neighb_u.erase(v);

        for (int w : neighb_u)
        {
            if (neighb_v.find(w) != neighb_v.end())
            {
                // TODO Ensure lexicographic order?
                triangles.push_back(std::make_pair(u, w));
            }
        }
    }

    for (int u : adj_list_[v])
    {
        adj_list_[u].insert(v);
    }

    return triangles;
}

// This is actually super easy.
std::vector<int> Graph::incident_triangles(ipair e) const
{
    std::vector<int> inter;
    std::set_intersection(e.first.begin(), e.first.end(),
                          e.second.begin(), e.second.end()
                          std::back_inserter(inter));
    return inter;
}


