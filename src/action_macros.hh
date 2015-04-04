// FIXME License notice

#ifndef ACTIONS_HH
#define ACTIONS_HH

#include "constant.hh"

// FIXME

#define CHECK_POSITIVE(n) if (n < 0) return VALEUR_INVALIDE;
#define CHECK_PA(num_pa) if (st->action_points(player_id_) < (num_pa)) return PA_INSUFFISANTS;
#define CHECK_POSITION(pos) if ((pos).x < 0 || (pos).y < 0 || (pos).x >= TAILLE_TERRAIN || (pos).y >= TAILLE_TERRAIN) return POSITION_INVALIDE;

#define CHECK_PORTAL_HERE() int portal_here = st->map()->portal_id_maybe(st->player_pos(player_id_)); if (portal_here == -1) return AUCUN_PORTAIL;
#define CHECK_PORTAL_THERE(pos) int portal_there = st->map()->portal_id_maybe(pos); if (portal_there == -1) return AUCUN_PORTAIL;

#define PROHIBIT_OWN_PORTAL(portal_id)     if (st->owner(portal_id) == player_id_) return PORTAIL_AMI;
#define PROHIBIT_NEUTRAL_PORTAL(portal_id) if (st->owner(portal_id) == -1) return PORTAIL_NEUTRE;
#define PROHIBIT_ENEMY_PORTAL(portal_id)   if (st->owner(portal_id) == st->get_opponent(player_id_)) return PORTAIL_ENNEMI;

#define PORTAL_HERE() int portal_here = st->map()->portal_id_maybe(st->player_pos(player_id_));
#define PORTAL_THERE(pos) int portal_there = st->map()->portal_id_maybe(pos);

#define CONSUME_PA(num_pa) st->action_points(player_id_) -= (num_pa);

#endif // !ACTIONS_HH
