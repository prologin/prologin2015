#ifndef MAP_HH_
# define MAP_HH_

#include <array>
#include <exception>
#include <vector>

#include "constant.hh"
#include "geometry.hh"

const int NOT_A_PORTAL_INT = -2;
const int NB_JOUEURS = 2;

// Build and return a human-readable string to represent a position.
std::string position_str(const position &p);

// Exception to raise when provided an invalid position.
class InvalidPosition : public std::exception
{
public:
    InvalidPosition(const position &p)
    {
        message_ = "Invalid position: " + position_str(p);
    }

    virtual const char* what() const noexcept
    {
        return message_.c_str();
    }

private:
    std::string message_;
};

class Map
{
public:
    Map();
    ~Map();

    void init_stupid_map();
    int load(std::istream& s);

    // Return whether "p" identifies a valid position on this map.  As one
    // could expect, this is the only method that does not raise an
    // InvalidPosition when provided an invalid position.
    bool valid_position(position p) const;

    // Return whether "p" contains a portal.
    bool is_portal(position p) const;

    // If "p" contains a portal, return its ID.  Return -1 otherwise.
    int portal_id_maybe(position p) const;

    // Getters for the list of portals.
    const std::vector<position>& get_portals() const;
    int num_portals() const;

    // Getter for the players' units starting positions.
    position get_start_position(int player_ordinal) const;

private:
    // Array of cells: each cell at position (x, y) is at index:
    //     (x * TAILLE_TERRAIN + y)
    // If the cell contains no portal, it holds -1.  It holds the portal ID
    // otherwise.
    std::array<int, TAILLE_TERRAIN*TAILLE_TERRAIN> portals_map_;

    // Quick access to the list of all portals so we do not have to go through
    // all portals_map_ to find portals.
    std::vector<position> portals_list_;

    // For each player, provides the initial unit position.
    std::array<position, NB_JOUEURS> start_positions_;
};

#endif // !MAP_HH_
