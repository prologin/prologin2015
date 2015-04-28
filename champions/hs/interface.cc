///
// This file has been generated, if you wish to
// modify it in a permanent way, please refer
// to the script file : gen/generator_haskell.rb
//

#include "Prologin_stub.h"
extern "C" {
  extern void __stginit_Prologin ( void );
}
#include "interface.hh"

extern "C" void haskell_init(){
  static bool done = false;
  if(!done){
    hs_init(0, 0);
    hs_add_root(__stginit_Prologin);
    done = true;
  }
}
static std::vector<void*> __internal_need_free;

template<typename Lang, typename Cxx>
Cxx lang2cxx(Lang in)
{
  return in;
}

template<>
std::string lang2cxx<char*, std::string>(char* in)
{
  return in;
}

template<typename Lang, typename Lang_array, typename Cxx>
std::vector<Cxx> lang2cxx_array(Lang_array in)
{
  std::vector<Cxx> out(in.length);
  for (size_t i = 0; i < in.length; ++i)
    out[i] = lang2cxx<Lang, Cxx>(in.datas[i]);
  return out;
}

template<typename Lang, typename Lang_array, typename Cxx>
std::vector<Cxx> lang2cxx_array_ptr(Lang_array* in)
{
  std::vector<Cxx> out(in->length);
  for (size_t i = 0; i < in->length; ++i)
    out[i] = lang2cxx<Lang, Cxx>(in->datas[i]);
  return out;
}

template<typename Lang, typename Cxx>
Lang cxx2lang(Cxx in)
{
  return in;
}

template<>
char* cxx2lang<char*, std::string>(std::string in)
{
  size_t l = in.length();
  char* out = (char *) malloc(l + 1);
  __internal_need_free.push_back(out);
  for (int i = 0; i < l; i++) out[i] = in[i];
  out[l] = 0;
  return out;
}

template<typename Lang, typename Lang_array, typename Cxx>
Lang_array cxx2lang_array(const std::vector<Cxx>& in)
{
  Lang_array out = { NULL, in.size() };
  out.datas = (Lang *)malloc((out.length) * sizeof(Lang));
  __internal_need_free.push_back(out.datas);
  for (int i = 0; i < out.length; ++i)
    out.datas[i] = cxx2lang<Lang, Cxx>(in[i]);
  return out;
}

template<typename Lang, typename Lang_array, typename Cxx>
Lang_array* cxx2lang_array_ptr(const std::vector<Cxx>& in)
{
  static Lang_array out; out = { NULL, in.size() };
  out.datas = (Lang *)malloc((out.length) * sizeof(Lang));
  __internal_need_free.push_back(out.datas);
  for (int i = 0; i < out.length; ++i)
    out.datas[i] = cxx2lang<Lang, Cxx>(in[i]);
  return &out;
}
template<>
__internal__cxx__position lang2cxx<position, __internal__cxx__position>(position in)
{
  __internal__cxx__position out;
  out.x = lang2cxx<int, int >(in.x);
  out.y = lang2cxx<int, int >(in.y);
  return out;
}

template<>
position cxx2lang<position, __internal__cxx__position>(__internal__cxx__position in)
{
  position out;
  out.x = cxx2lang<int, int >(in.x);
  out.y = cxx2lang<int, int >(in.y);
  return out;
}

template<>
__internal__cxx__position lang2cxx<position*, __internal__cxx__position>(position* in)
{
  __internal__cxx__position out;
  out.x = lang2cxx<int, int >(in->x);
  out.y = lang2cxx<int, int >(in->y);
  return out;
}

template<>
position* cxx2lang<position*, __internal__cxx__position>(__internal__cxx__position in)
{
  static position out;
  out.x = cxx2lang<int, int >(in.x);
  out.y = cxx2lang<int, int >(in.y);
  return &out;
}

template<>
__internal__cxx__lien lang2cxx<lien, __internal__cxx__lien>(lien in)
{
  __internal__cxx__lien out;
  out.extr1 = lang2cxx<position, __internal__cxx__position >(in.extr1);
  out.extr2 = lang2cxx<position, __internal__cxx__position >(in.extr2);
  out.joueur_l = lang2cxx<int, int >(in.joueur_l);
  return out;
}

template<>
lien cxx2lang<lien, __internal__cxx__lien>(__internal__cxx__lien in)
{
  lien out;
  out.extr1 = cxx2lang<position, __internal__cxx__position >(in.extr1);
  out.extr2 = cxx2lang<position, __internal__cxx__position >(in.extr2);
  out.joueur_l = cxx2lang<int, int >(in.joueur_l);
  return out;
}

template<>
__internal__cxx__lien lang2cxx<lien*, __internal__cxx__lien>(lien* in)
{
  __internal__cxx__lien out;
  out.extr1 = lang2cxx<position, __internal__cxx__position >(in->extr1);
  out.extr2 = lang2cxx<position, __internal__cxx__position >(in->extr2);
  out.joueur_l = lang2cxx<int, int >(in->joueur_l);
  return out;
}

template<>
lien* cxx2lang<lien*, __internal__cxx__lien>(__internal__cxx__lien in)
{
  static lien out;
  out.extr1 = cxx2lang<position, __internal__cxx__position >(in.extr1);
  out.extr2 = cxx2lang<position, __internal__cxx__position >(in.extr2);
  out.joueur_l = cxx2lang<int, int >(in.joueur_l);
  return &out;
}

template<>
__internal__cxx__champ lang2cxx<champ, __internal__cxx__champ>(champ in)
{
  __internal__cxx__champ out;
  out.som1 = lang2cxx<position, __internal__cxx__position >(in.som1);
  out.som2 = lang2cxx<position, __internal__cxx__position >(in.som2);
  out.som3 = lang2cxx<position, __internal__cxx__position >(in.som3);
  out.joueur_c = lang2cxx<int, int >(in.joueur_c);
  return out;
}

template<>
champ cxx2lang<champ, __internal__cxx__champ>(__internal__cxx__champ in)
{
  champ out;
  out.som1 = cxx2lang<position, __internal__cxx__position >(in.som1);
  out.som2 = cxx2lang<position, __internal__cxx__position >(in.som2);
  out.som3 = cxx2lang<position, __internal__cxx__position >(in.som3);
  out.joueur_c = cxx2lang<int, int >(in.joueur_c);
  return out;
}

template<>
__internal__cxx__champ lang2cxx<champ*, __internal__cxx__champ>(champ* in)
{
  __internal__cxx__champ out;
  out.som1 = lang2cxx<position, __internal__cxx__position >(in->som1);
  out.som2 = lang2cxx<position, __internal__cxx__position >(in->som2);
  out.som3 = lang2cxx<position, __internal__cxx__position >(in->som3);
  out.joueur_c = lang2cxx<int, int >(in->joueur_c);
  return out;
}

template<>
champ* cxx2lang<champ*, __internal__cxx__champ>(__internal__cxx__champ in)
{
  static champ out;
  out.som1 = cxx2lang<position, __internal__cxx__position >(in.som1);
  out.som2 = cxx2lang<position, __internal__cxx__position >(in.som2);
  out.som3 = cxx2lang<position, __internal__cxx__position >(in.som3);
  out.joueur_c = cxx2lang<int, int >(in.joueur_c);
  return &out;
}

extern "C" erreur hs_capturer(void)
{
  return cxx2lang<erreur, erreur >(api_capturer());
}

extern "C" erreur hs_lier(position* portail)
{
  return cxx2lang<erreur, erreur >(api_lier(lang2cxx<position*, __internal__cxx__position >(portail)));
}

extern "C" erreur hs_neutraliser(void)
{
  return cxx2lang<erreur, erreur >(api_neutraliser());
}

extern "C" erreur hs_deplacer(position* dest)
{
  return cxx2lang<erreur, erreur >(api_deplacer(lang2cxx<position*, __internal__cxx__position >(dest)));
}

extern "C" erreur hs_ajouter_bouclier(void)
{
  return cxx2lang<erreur, erreur >(api_ajouter_bouclier());
}

extern "C" erreur hs_utiliser_virus(void)
{
  return cxx2lang<erreur, erreur >(api_utiliser_virus());
}

extern "C" erreur hs_utiliser_turbo(void)
{
  return cxx2lang<erreur, erreur >(api_utiliser_turbo());
}

extern "C" lien_array* hs_liste_liens(void)
{
  return cxx2lang_array_ptr<lien, lien_array, __internal__cxx__lien >(api_liste_liens());
}

extern "C" champ_array* hs_liste_champs(void)
{
  return cxx2lang_array_ptr<champ, champ_array, __internal__cxx__champ >(api_liste_champs());
}

extern "C" position_array* hs_liste_portails(void)
{
  return cxx2lang_array_ptr<position, position_array, __internal__cxx__position >(api_liste_portails());
}

extern "C" lien_array* hs_liens_bloquants(position* ext1, position* ext2)
{
  return cxx2lang_array_ptr<lien, lien_array, __internal__cxx__lien >(api_liens_bloquants(lang2cxx<position*, __internal__cxx__position >(ext1), lang2cxx<position*, __internal__cxx__position >(ext2)));
}

extern "C" bool hs_lien_existe(position* ext1, position* ext2)
{
  return cxx2lang<bool, bool >(api_lien_existe(lang2cxx<position*, __internal__cxx__position >(ext1), lang2cxx<position*, __internal__cxx__position >(ext2)));
}

extern "C" bool hs_champ_existe(position* som1, position* som2, position* som3)
{
  return cxx2lang<bool, bool >(api_champ_existe(lang2cxx<position*, __internal__cxx__position >(som1), lang2cxx<position*, __internal__cxx__position >(som2), lang2cxx<position*, __internal__cxx__position >(som3)));
}

extern "C" bool hs_case_dans_champ(position* pos)
{
  return cxx2lang<bool, bool >(api_case_dans_champ(lang2cxx<position*, __internal__cxx__position >(pos)));
}

extern "C" champ_array* hs_case_champs(position* pos)
{
  return cxx2lang_array_ptr<champ, champ_array, __internal__cxx__champ >(api_case_champs(lang2cxx<position*, __internal__cxx__position >(pos)));
}

extern "C" int hs_portail_joueur(position* portail)
{
  return cxx2lang<int, int >(api_portail_joueur(lang2cxx<position*, __internal__cxx__position >(portail)));
}

extern "C" int hs_portail_boucliers(position* portail)
{
  return cxx2lang<int, int >(api_portail_boucliers(lang2cxx<position*, __internal__cxx__position >(portail)));
}

extern "C" lien_array* hs_liens_incidents_portail(position* portail)
{
  return cxx2lang_array_ptr<lien, lien_array, __internal__cxx__lien >(api_liens_incidents_portail(lang2cxx<position*, __internal__cxx__position >(portail)));
}

extern "C" champ_array* hs_champs_incidents_portail(position* portail)
{
  return cxx2lang_array_ptr<champ, champ_array, __internal__cxx__champ >(api_champs_incidents_portail(lang2cxx<position*, __internal__cxx__position >(portail)));
}

extern "C" champ_array* hs_champs_incidents_segment(position* ext1, position* ext2)
{
  return cxx2lang_array_ptr<champ, champ_array, __internal__cxx__champ >(api_champs_incidents_segment(lang2cxx<position*, __internal__cxx__position >(ext1), lang2cxx<position*, __internal__cxx__position >(ext2)));
}

extern "C" position_array* hs_hist_portails_captures(void)
{
  return cxx2lang_array_ptr<position, position_array, __internal__cxx__position >(api_hist_portails_captures());
}

extern "C" position_array* hs_hist_portails_neutralises(void)
{
  return cxx2lang_array_ptr<position, position_array, __internal__cxx__position >(api_hist_portails_neutralises());
}

extern "C" lien_array* hs_hist_liens_crees(void)
{
  return cxx2lang_array_ptr<lien, lien_array, __internal__cxx__lien >(api_hist_liens_crees());
}

extern "C" champ_array* hs_hist_champs_crees(void)
{
  return cxx2lang_array_ptr<champ, champ_array, __internal__cxx__champ >(api_hist_champs_crees());
}

extern "C" position_array* hs_hist_boucliers_ajoutes(void)
{
  return cxx2lang_array_ptr<position, position_array, __internal__cxx__position >(api_hist_boucliers_ajoutes());
}

extern "C" int hs_distance(position* pos1, position* pos2)
{
  return cxx2lang<int, int >(api_distance(lang2cxx<position*, __internal__cxx__position >(pos1), lang2cxx<position*, __internal__cxx__position >(pos2)));
}

extern "C" int hs_score_triangle(position* som1, position* som2, position* som3)
{
  return cxx2lang<int, int >(api_score_triangle(lang2cxx<position*, __internal__cxx__position >(som1), lang2cxx<position*, __internal__cxx__position >(som2), lang2cxx<position*, __internal__cxx__position >(som3)));
}

extern "C" bool hs_intersection_segments(position* a1, position* a2, position* b1, position* b2)
{
  return cxx2lang<bool, bool >(api_intersection_segments(lang2cxx<position*, __internal__cxx__position >(a1), lang2cxx<position*, __internal__cxx__position >(a2), lang2cxx<position*, __internal__cxx__position >(b1), lang2cxx<position*, __internal__cxx__position >(b2)));
}

extern "C" bool hs_point_dans_triangle(position* p, position* som1, position* som2, position* som3)
{
  return cxx2lang<bool, bool >(api_point_dans_triangle(lang2cxx<position*, __internal__cxx__position >(p), lang2cxx<position*, __internal__cxx__position >(som1), lang2cxx<position*, __internal__cxx__position >(som2), lang2cxx<position*, __internal__cxx__position >(som3)));
}

extern "C" int hs_moi(void)
{
  return cxx2lang<int, int >(api_moi());
}

extern "C" int hs_adversaire(void)
{
  return cxx2lang<int, int >(api_adversaire());
}

extern "C" position* hs_position_agent(int id_joueur)
{
  return cxx2lang<position*, __internal__cxx__position >(api_position_agent(lang2cxx<int, int >(id_joueur)));
}

extern "C" int hs_points_action(void)
{
  return cxx2lang<int, int >(api_points_action());
}

extern "C" int hs_points_deplacement(void)
{
  return cxx2lang<int, int >(api_points_deplacement());
}

extern "C" int hs_score(int id_joueur)
{
  return cxx2lang<int, int >(api_score(lang2cxx<int, int >(id_joueur)));
}

extern "C" int hs_tour_actuel(void)
{
  return cxx2lang<int, int >(api_tour_actuel());
}

extern "C" bool hs_annuler(void)
{
  return cxx2lang<bool, bool >(api_annuler());
}

extern "C" void hs_afficher_erreur(erreur v)
{
  api_afficher_erreur(lang2cxx<erreur, erreur >(v));
}

extern "C" void hs_afficher_position(position* v)
{
  api_afficher_position(lang2cxx<position*, __internal__cxx__position >(v));
}

extern "C" void hs_afficher_lien(lien* v)
{
  api_afficher_lien(lang2cxx<lien*, __internal__cxx__lien >(v));
}

extern "C" void hs_afficher_champ(champ* v)
{
  api_afficher_champ(lang2cxx<champ*, __internal__cxx__champ >(v));
}

extern "C" void partie_init(){
  haskell_init();
  hs_partie_init();
  hs_perform_gc();
  for(void* ptr : __internal_need_free){
    free(ptr);
  }
  __internal_need_free.clear();
}
extern "C" void jouer_tour(){
  haskell_init();
  hs_jouer_tour();
  hs_perform_gc();
  for(void* ptr : __internal_need_free){
    free(ptr);
  }
  __internal_need_free.clear();
}
extern "C" void partie_fin(){
  haskell_init();
  hs_partie_fin();
  hs_perform_gc();
  for(void* ptr : __internal_need_free){
    free(ptr);
  }
  __internal_need_free.clear();
}
