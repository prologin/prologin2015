#ifndef MAP_HH_
# define MAP_HH_

#include <array>
#include <vector>

#include "constant.hh"

const int NOT_A_PORTAL_INT = -2;
const int NB_JOUEURS = 2;

class Map
{
public:
    Map();
    Map(const Map& map);
    ~Map();

    void init_stupid_map();
    int load(std::istream& s);

    bool valid_position(position p) const;

    int portal_id_maybe(position p) const;
    bool is_portal(position p) const;

    const std::vector<position>& get_portals() const;
    int num_portals() const;

    position get_start_position(int player_ordinal) const;

private:
    std::array<bool, TAILLE_TERRAIN*TAILLE_TERRAIN> portals_map_;
    std::vector<position> portals_list_;
    std::array<position, NB_JOUEURS> start_positions_;
};

#endif // !MAP_HH_
