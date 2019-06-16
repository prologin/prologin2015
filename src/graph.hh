// FIXME License notice

#ifndef GRAPH_HH
#define GRAPH_HH

#include "constant.hh"

#include <set>
#include <tuple>
#include <utility>
#include <vector>

typedef std::pair<int, int> ipair;
typedef std::tuple<int, int, int> itriple;
ipair ordered_pair(int a, int b);
itriple ordered_triple(int a, int b, int c);

class Graph
{
public:
    Graph(int size);
    Graph(const Graph& g);

    bool edge_exists(ipair e) const;
    void add_edge(ipair e);
    void remove_edge(ipair e);
    void remove_incident_edges(int v);

    const std::vector<std::set<int>>& adj_list() const { return adj_list_; }

    // This interface causes unnecessary copying
    // but iterators and higher-order functions are too cumbersome…
    // TODO: memoize to avoid recomputing when nothing has changed
    std::vector<ipair> edges() const;
    std::vector<itriple> triangles() const;
    std::vector<ipair> incident_triangles(int v) const;
    std::vector<int> incident_triangles(ipair e) const;

private:
    std::vector<std::set<int>> adj_list_;
};

#endif /* !GRAPH_HH */
