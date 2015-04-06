#include <istream>
#include <string>
#include <sstream>
#include <map>
#include <array>

#include <utils/log.hh>
#include <rules/player.hh>

#include "constant.hh"
#include "map.hh"


std::string position_str(const position &p)
{
    std::ostringstream s;
    s << "(" << p.x << ", " << p.y << ")";
    return s.str();
}

Map::Map()
{
    portals_map_.fill(-1);
}

Map::~Map()
{
}

void Map::init_stupid_map()
{
    portals_list_ = {{10,10},{10,20},{20,10},{20,20}};
    start_positions_[0] = {5,5};
    start_positions_[1] = {25,25};
    
    int count = 0;
    for (auto& pos : portals_list_)
    {
        portals_map_[index(pos)] = count;
        count++;
    }
}

int Map::load(std::istream& s)
{
    INFO("Loading map");

    std::string line;

    for (int i = 0; i < 2; i++)
    {
        s >> start_positions_[i].x >> start_positions_[i].y;
        INFO("Player %d starting position is x=%d, y=%d",
                i, start_positions_[i].x, start_positions_[i].y);
        if (!valid_position((position){.x = start_positions_[i].x,
                                       .y = start_positions_[i].y}))
            switch(i) {
            case 0:
                FATAL("starting position for first player is invalid");
                break;
            case 1:
                FATAL("starting position for second player is invalid");
                break;
            default:
                FATAL("dead code elimination should remove this");
                break;
            }

    }

    for (int y = 0; y < TAILLE_TERRAIN; ++y) // y then x is correct!
    {
        s >> line;

        if (line.length() != (size_t) TAILLE_TERRAIN)
            FATAL("map: line %d is too short or too long "
                  "(is %d long, should be %d)",
                    y, line.length(), TAILLE_TERRAIN);

        for (int x = 0; x < TAILLE_TERRAIN; ++x)
        {
            switch (line[x])
            {
            case 'X':
                portals_map_[index({x, y})] = 0;
                break;
            case '.':
                break;
            default:
                FATAL("Invalid cell at y=%d x=%d", y, x);
                break;
            }
        }
    }

    // Some contortions to ensure portals are numbered in
    // lexicographical order with x first, y second
    int count = 0;

    for (int x = 0; x < TAILLE_TERRAIN; ++x)
    {
        for (int y = 0; y < TAILLE_TERRAIN; ++y)
        {
            const position p = {x, y};
            if (portals_map_[index(p)] == 0)
            {
                portals_map_[index(p)] = count;
                count++;
                portals_list_.push_back(p);
            }
        }
    }

                
    return 0;
}

bool Map::valid_position(position p)
{
    return 0 <= p.x && p.x < TAILLE_TERRAIN &&
           0 <= p.y && p.y < TAILLE_TERRAIN;
}

int Map::portal_id_maybe(position p) const
{
    if (!valid_position(p))
        throw InvalidPosition(p);
    return portals_map_[index(p)];
}

bool Map::is_portal(position p) const
{
    if (!valid_position(p))
        throw InvalidPosition(p);
    return portals_map_[index(p)] != -1;
}

const std::vector<position>& Map::get_portals() const
{
    return portals_list_;
}

int Map::num_portals() const
{
    return portals_list_.size();
}

position Map::get_start_position(int i) const
{
    if (0 <= i && i < 2)
        return start_positions_[i];
    return { -1, -1 };
}
