// FIXME License notice

#ifndef GEOMETRY_HH
#define GEOMETRY_HH

#include "constant.hh"

#include <cstdlib>
#include <string>

inline bool operator==(const position& a, const position& b)
{
    return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const position& a, const position& b)
{
    return !(a == b);
}

inline int l1_norm(int x, int y)
{
    return abs(x) + abs(y);
}

// a.k.a Manhattan distance
inline int l1_distance(int x1, int y1, int x2, int y2)
{
    return l1_norm(x1 - x2, y1 - y2);
}
inline int l1_distance(const position& a, const position& b)
{
    return l1_distance(a.x, a.y, b.x, b.y);
}

// determinant of vectors (x1,y1) and (x2,y2)
inline int determinant(int x1, int y1, int x2, int y2)
{
    return x1 * y2 - x2 * y1;
}
// det(\vec{AB}, \vec{CD})
inline int determinant(const position& a, const position& b, const position& c,
                       const position& d)
{
    return determinant(b.x - a.x, b.y - a.y, d.x - c.x, d.y - c.y);
}

// Test the intersection of two segments,
// more precisely, if one of the following conditions holds:
// * [AB] intersects ]CD[
// * ]AB[ intersects [CD]
bool segments_intersect(const position& a, const position& b, const position& c,
                        const position& d);

// Test whether a point P is inside the *interior* of the triangle ABC
// (i.e. excluding the boundary)
bool point_in_triangle(const position& a, const position& b, const position& c,
                       const position& p);

// Build and return a human-readable string to represent a position.
std::string position_str(const position& p);

#endif /* !GEOMETRY_HH */
