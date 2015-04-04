// FIXME License notice

#ifndef ACTIONS_HH
#define ACTIONS_HH

#include "constant.hh"

// FIXME

#define CHECK_POSITIVE(n) if (n < 0) return VALEUR_INVALIDE;
#define CHECK_PA(num_pa) if (TODO < (num_pa)) return PA_INSUFFISANTS;
#define CHECK_POSITION(pos) if ((pos).x < 0 || (pos).y < 0 || (pos).x >= TAILLE_TERRAIN || (pos).y >= TAILLE_TERRAIN) return POSITION_INVALIDE;

#define CHECK_PORTAL_HERE() int portal_here = TODO; if (portal_here == -1) return AUCUN_PORTAIL;
#define CHECK_PORTAL_THERE(pos) int portal_there = TODO(pos); if (portal_there == -1) return AUCUN_PORTAIL;

#define PROHIBIT_OWN_PORTAL(portal_id)     TODO
#define PROHIBIT_NEUTRAL_PORTAL(portal_id) TODO
#define PROHIBIT_ENEMY_PORTAL(portal_id)   TODO


#define PORTAL_HERE() int portal_here = TODO;
#define PORTAL_THERE(pos) int portal_there = TODO(pos);

#define CONSUME_PA(num_pa) TODO -= (num_pa);

#endif // !ACTIONS_HH
