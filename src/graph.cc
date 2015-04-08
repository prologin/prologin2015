#include <algorithm>

#include "graph.hh"

ipair ordered_pair(int a, int b)
{
    if (a > b)
        std::swap(a, b);
    return std::make_pair(a,b);
}

// Size 3 sorting network
itriple ordered_triple(int a, int b, int c)
{
    // b, c = min(b, c), max(b,c)
    if (b > c)
        std::swap(b,c);
    // a, b = min(a, b), max(a, b)
    if (a > b)
        std::swap(a,b);
    // a is now minimal, swap b and c if necessary
    if (b > c)
        std::swap(b,c);
    return std::make_tuple(a, b, c);
}

Graph::Graph(int size)
    : adj_list_(size)
{
}

Graph::Graph(const Graph& g)
    : adj_list_(g.adj_list_)
{
}


bool Graph::edge_exists(ipair e) const
{
    auto s = adj_list_[e.first];
    return s.find(e.second) != s.end(); // lolSTL lawlSTL LOLSTL
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
    for (unsigned int i = 0; i < adj_list_.size(); ++i)
    {
        auto neighb = adj_list_[i];
        // Trick to eliminate duplicates: iterate only on elements higher than i
        // Consequence: the vertices of an edge are given in order
        for (auto p = neighb.upper_bound(i); p != neighb.end(); ++p)
        {
            edges.push_back(std::make_pair(i, *p));
        }
    }
    return edges;
}

// For planar graphs, this algorithm is *linear* in the number of edges!
// (actually, with this implementation, it's more like O(n log n))
// Reference: "Arboricity and subgraph listing algorithms",
//            Chiba & Nishizeki, 1985, SIAM. J. Comput.
std::vector<itriple> Graph::triangles() const
{
    std::vector<int> degree_order(adj_list_.size(), 0);
    for (unsigned int i = 0; i < adj_list_.size(); ++i)
    {
        degree_order[i] = i;
    }
    std::sort(degree_order.begin(), degree_order.end(),
              [this](int u, int v)
              { return adj_list_[u].size() > adj_list_[v].size(); });

    // do a copy of the adjacency list, since we're going to mutate it
    // and we want to respect const-correctness
    auto adj_list_copy = adj_list_;
 
    std::vector<itriple> triangles;
    for (int v : degree_order)
    {
        for (int u : adj_list_copy[v])
        {
            auto& neighb_u = adj_list_copy[u];

            // Ensures no duplication, and also crucial for the complexity
            neighb_u.erase(v);

            for (int w : neighb_u)
            {
                auto& neighb_w = adj_list_copy[w];
                if (neighb_w.find(v) != neighb_w.end())
                {
                    triangles.push_back(ordered_triple(u, v, w));
                }
            }
        }
    }

    return triangles;
}

// Basically, enumerate edges between neighbours of v
std::vector<ipair> Graph::incident_triangles(int v) const
{
    std::vector<ipair> triangles;

    auto& neighb_v = adj_list_[v];
    for (int u : neighb_v)
    {
        auto& neighb_u = adj_list_[u];
        for (auto p = neighb_u.upper_bound(u); p != neighb_u.end(); ++p)
        {
            if (neighb_v.find(*p) != neighb_v.end())
                triangles.push_back(std::make_pair(u, *p));
        }
    }

    return triangles;
}

// This is actually super easy.
std::vector<int> Graph::incident_triangles(ipair e) const
{
    std::vector<int> inter;
    auto& neighb_1 = adj_list_[e.first];
    auto& neighb_2 = adj_list_[e.second];
    std::set_intersection(neighb_1.begin(), neighb_1.end(),
                          neighb_2.begin(), neighb_2.end(),
                          std::back_inserter(inter));
    return inter;
}


