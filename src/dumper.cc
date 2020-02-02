/*
** prologin2015 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** prologin2015 is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with prologin2015.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cstdlib>
#include <cstring>
#include <sstream>

#include <rules/action.hh>
#include <rules/actions.hh>
#include <utils/buffer.hh>

#include "dumper.hh"

#include "constant.hh"
#include "game_state.hh"
#include "graph.hh"
#include "map.hh"

/* Put some binary content as a JSON string in the output stream. */
static void dump_binary(std::ostream& ss, const uint8_t bytes[], unsigned size)
{
    const char* hextable = "0123456789ABCDEF";

    ss << "\"";
    for (unsigned i = 0; i < size; ++i)
    {
        if (bytes[i] == '"')
            ss << "\\\"";
        else if (bytes[i] == '\\')
            ss << "\\\\";
        else if (0x20 <= bytes[i] && bytes[i] <= 0x7e)
            ss << (char)bytes[i];
        else
            ss << "\\u00" << hextable[bytes[i] >> 4]
               << hextable[bytes[i] & 0x0f];
    }
    ss << "\"";
}

/* Dump everything that describe players: score and position on the map.  */

static void dump_players(std::ostream& ss, const GameState& st)
{
    auto& players = st.get_players();
    bool is_first = true;

    ss << "{";
    for (unsigned i = 0; i < players.size(); ++i)
    {
        const int id = players[i]->id;
        const position& pos = st.player_pos(id);

        if (players[i]->type != rules::PLAYER)
            continue;

        if (!is_first)
            ss << ", ";
        is_first = false;
        ss << "\"" << id << "\": {"
           << "\"name\": ";
        dump_binary(ss,
                    reinterpret_cast<const uint8_t*>(players[i]->name.c_str()),
                    players[i]->name.size());
        ss << ", "
           << "\"x\": " << pos.x << ", "
           << "\"y\": " << pos.y << ", "
           << "\"score\": " << players[i]->score << "}";
    }
    ss << "}";
}

/* Dump everything that describe the map: portals, shields, edges and
   vertices.  */

static void dump_map(std::ostream& ss, const GameState& st)
{
    const Map& map = st.map();
    bool is_first;

    ss << "{";

    /* For all portals, dump the position, the owner ID (-1 for no owner) and
       the shield "value".  */
    ss << "\"portals\": [";
    is_first = true;
    for (const position& portal : map.get_portals())
    {
        const int portal_id = map.portal_id_maybe(portal);
        const int owner = st.owner(portal_id);
        if (!is_first)
            ss << ", ";
        is_first = false;
        ss << "{"
           << "\"x\": " << portal.x << ", "
           << "\"y\": " << portal.y << ", "
           << "\"shields\": " << st.num_shields(portal_id) << ", ";
        if (owner == -1)
            ss << "\"owner\": null";
        else
            ss << "\"owner\": " << st.owner(portal_id);
        ss << "}";
    }
    ss << "], ";

    /* Dump all edges between portals.  Vertices are portal indices.  */
    ss << "\"edges\": [";
    is_first = true;
    for (const ipair& edge : st.graph().edges())
    {
        if (!is_first)
            ss << ", ";
        is_first = false;
        ss << "{"
           << "\"from\": " << edge.first << ", "
           << "\"to\": " << edge.second << "}";
    }
    ss << "], ";

    /* Dump all triangles.  Here too, vertices are portal indices.  */
    ss << "\"triangles\": [";
    is_first = true;
    for (const itriple& triangle : st.graph().triangles())
    {
        if (!is_first)
            ss << ", ";
        is_first = false;
        ss << "{"
           << "\"s0\": " << std::get<0>(triangle) << ", "
           << "\"s1\": " << std::get<1>(triangle) << ", "
           << "\"s2\": " << std::get<2>(triangle) << "}";
    }

    ss << "]"
       << "}";
}

static void dump_actions(std::ostream& ss, rules::Actions& acts)
{
    utils::Buffer buf;
    acts.handle_buffer(buf);
    dump_binary(ss, buf.data(), buf.size());
}

/* Return a JSON representation of the given GameState, including the given
   list of actions.  The returned string is heap-allocated and must be delete'd
   by the caller.  The JSON tree fits in one line (i.e. it doesn't contain a
   new line character), making it easy to maintain a collection of dumps in a
   text file.  */
char* dump_game_state(const GameState& st, rules::Actions& acts)
{
    std::stringstream ss;

    ss << "{";

    // - "turn": [current turn, number of turns]
    ss << "\"turn\": [" << st.get_current_round() << ", " << NB_TOURS << "] ";

    ss << ", "
       << "\"players\": ";
    dump_players(ss, st);

    ss << ", "
       << "\"map\": ";
    dump_map(ss, st);

    ss << ", "
       << "\"actions\": ";
    dump_actions(ss, acts);

    ss << "}";

    /* Use malloc(), since the caller will use free(). */
    char* result = (char*)malloc(sizeof(char) * ss.str().size() + 1);

    strcpy(result, ss.str().c_str());
    return result;
}
