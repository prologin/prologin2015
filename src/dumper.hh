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

#ifndef DUMPER_HH_
#define DUMPER_HH_

#include <rules/actions.hh>

#include "game_state.hh"

char* dump_game_state(const GameState& st, rules::Actions& acts);

#endif // !DUMPER_HH_
