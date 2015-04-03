#include <algorithm>

#include "geometry.hh"

// The two following functions are inspired from CLRS chapter 33
// TODO: have fun with useless micro-optimizations

// Test whether C \in [AB] when we know that A, B and C are collinear
inline bool on_segment(const position& a, const position& b, const position& c)
{
    return std::min(a.x, b.x) <= c.x && c.x <= std::max(a.x, b.x)
        && std::min(a.y, b.y) <= c.y && c.y <= std::max(a.y, b.y);
}

// Test the intersection of two segments,
// more precisely, if one of the following conditions holds:
// * [AB] intersects ]CD[
// * ]AB[ intersects [CD]
bool segments_intersect(const position& a, const position& b,
                        const position& c, const position& d)
{
    int d1 = determinant(c, d, c, a);
    int d2 = determinant(c, d, c, b);
    int d3 = determinant(a, b, a, c);
    int d4 = determinant(a, b, a, d);

    // Cormen et al. write 'if (...) return true; else if ...' LOL
    return (d1*d2 < 0 && d3*d4 < 0) // ]AB[ intersects ]CD[
        || (d1 == 0 && on_segment(c, d, a) && a != c && a != d)
        || (d2 == 0 && on_segment(c, d, b) && b != c && b != d)
        || (d3 == 0 && on_segment(a, b, c) && c != a && c != b)
        || (d4 == 0 && on_segment(a, b, d) && d != a && d != b);
}

