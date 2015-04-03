// FIXME License notice

#ifndef GEOMETRY_HH
#define GEOMETRY_HH

#include "constant.hh"

inline bool operator==(const position& a, const position& b)
{
    return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const position& a, const position& b)
{
    return !(a == b);
}

inline int determinant(int x1, int y1, int x2, int y2)
{
    return x1*y2 - x2*y1;
}

inline int determinant(const position& a, const position& b,
                       const position& c, const position& d)
{
    return determinant(b.x-a.x, b.y-a.y, d.x-c.x, d.y-c.y);
}

bool segments_intersect(const position& a, const position& b,
                        const position& c, const position& d);

bool point_in_triangle(const position& a, const position& b, const position& c,
                       const position& p);

#endif /* !GEOMETRY_HH */

