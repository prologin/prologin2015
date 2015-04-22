/*
** Stechec project is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** The complete GNU General Public Licence Notice can be found as the
** `NOTICE' file in the root directory.
**
** Copyright (C) 2015 Prologin
*/

#include "api.hh"

#include <iostream>
#include <sstream>
#include <vector>

// from api.cc
extern Api* api;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& arr)
{
  os << "[";
  typename std::vector<T>::const_iterator it;
  for (it = arr.begin(); it != arr.end(); ++it)
  {
    if (it != arr.begin())
      os << ", ";
    os << *it;
  }
  os << "]";
  return os;
}


// todo avoir un ostringstream a la place de std::string

std::string convert_to_string(int i){
  std::ostringstream s;
  s << i;
  std::string result = s.str();
  return result;
}
std::string convert_to_string(std::string i){
  return i;
}
std::string convert_to_string(bool i){
  return i?"true":"false";
}
std::string convert_to_string(std::vector<int> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(erreur in){
  switch (in)
  {
    case OK: return "\"ok\"";
    case PA_INSUFFISANTS: return "\"pa_insuffisants\"";
    case AUCUN_PORTAIL: return "\"aucun_portail\"";
    case POSITION_INVALIDE: return "\"position_invalide\"";
    case POSITION_ELOIGNEE: return "\"position_eloignee\"";
    case PORTAIL_AMI: return "\"portail_ami\"";
    case PORTAIL_NEUTRE: return "\"portail_neutre\"";
    case PORTAIL_ENNEMI: return "\"portail_ennemi\"";
    case LIEN_INTERSECTION: return "\"lien_intersection\"";
    case LIEN_CHAMP: return "\"lien_champ\"";
    case LIMITE_BOUCLIERS: return "\"limite_boucliers\"";
  }
  return "bad value";
}
std::string convert_to_string(std::vector<erreur> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(position in){
  std::string x = convert_to_string(in.x);
  std::string y = convert_to_string(in.y);
  std::string out = "{";
  out += "x:" + x;
  out += ", ";
  out += "y:" + y;
  return out + "}";
}

std::string convert_to_string(std::vector<position> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(lien in){
  std::string extr1 = convert_to_string(in.extr1);
  std::string extr2 = convert_to_string(in.extr2);
  std::string joueur = convert_to_string(in.joueur);
  std::string out = "{";
  out += "extr1:" + extr1;
  out += ", ";
  out += "extr2:" + extr2;
  out += ", ";
  out += "joueur:" + joueur;
  return out + "}";
}

std::string convert_to_string(std::vector<lien> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
std::string convert_to_string(champ in){
  std::string som1 = convert_to_string(in.som1);
  std::string som2 = convert_to_string(in.som2);
  std::string som3 = convert_to_string(in.som3);
  std::string joueur = convert_to_string(in.joueur);
  std::string out = "{";
  out += "som1:" + som1;
  out += ", ";
  out += "som2:" + som2;
  out += ", ";
  out += "som3:" + som3;
  out += ", ";
  out += "joueur:" + joueur;
  return out + "}";
}

std::string convert_to_string(std::vector<champ> in){
  if (in.size()){
    std::string s = "[" + convert_to_string(in[0]);
    for (int i = 1, l = in.size(); i < l; i++){
      s = s + ", " + convert_to_string(in[i]);
    }
    return s + "]";
  }else{
    return "[]";
  }
}
///
// Capture le portail où est positionné votre agent.
//
extern "C" erreur api_capturer()
{
  return api->capturer();
}

///
// Crée un lien entre le portail où se trouve votre agent et le portail de destination donné en argument.
//
extern "C" erreur api_lier(position portail)
{
  return api->lier(portail);
}

///
// Neutralise le portail où se trouve votre agent.
//
extern "C" erreur api_neutraliser()
{
  return api->neutraliser();
}

///
// Déplace votre agent sur la case passée en argument.
//
extern "C" erreur api_deplacer(position dest)
{
  return api->deplacer(dest);
}

///
// Ajoute un bouclier au portail sur lequel se trouve votre agent.
//
extern "C" erreur api_ajouter_bouclier()
{
  return api->ajouter_bouclier();
}

///
// Fait passer le portail où se situe votre agent à l'autre joueur.
//
extern "C" erreur api_utiliser_virus()
{
  return api->utiliser_virus();
}

///
// Utilise un turbo.
//
extern "C" erreur api_utiliser_turbo()
{
  return api->utiliser_turbo();
}

///
// Renvoie la liste de tous les liens présents.
//
extern "C" std::vector<lien> api_liste_liens()
{
  return api->liste_liens();
}

///
// Renvoie la liste de tous les champs de contrôle.
//
extern "C" std::vector<champ> api_liste_champs()
{
  return api->liste_champs();
}

///
// Renvoie la liste de tous les portails de la carte.
//
extern "C" std::vector<position> api_liste_portails()
{
  return api->liste_portails();
}

///
// Renvoie la liste de tous les liens existants qui croisent un segment, entravant la création d'un lien.
//
extern "C" std::vector<lien> api_liens_bloquants(position ext1, position ext2)
{
  return api->liens_bloquants(ext1, ext2);
}

///
// Renvoie le numéro du joueur contrôlant le lien donné, -1 si le lien n'existe pas (mais les deux positions sont bien des portails). Vous pouvez utiliser cette fonction pour vérifier si deux portails sont reliés.
//
extern "C" int api_lien_joueur(position ext1, position ext2)
{
  return api->lien_joueur(ext1, ext2);
}

///
// Renvoie un booléen indiquant si les 3 positions repèrent bien 3 portails tous reliés entre eux.
//
extern "C" bool api_champ_existe(position som1, position som2, position som3)
{
  return api->champ_existe(som1, som2, som3);
}

///
// Renvoie un booléen indiquant si la case ``pos`` se trouve dans un champ.
//
extern "C" bool api_case_dans_champ(position pos)
{
  return api->case_dans_champ(pos);
}

///
// Renvoie la liste des champs à l'intérieur desquels ``pos`` se trouve. Si la case est un portail, le résultat de ``case_champs`` sera disjoint de celui de ``champs_incidents_portail``.
//
extern "C" std::vector<champ> api_case_champs(position pos)
{
  return api->case_champs(pos);
}

///
// Renvoie le numéro du joueur correspondant au portail donné, -1 si le portail est neutre, -2 si la case n'est pas un portail. Vous pouvez utiliser cette fonction pour vérifier qu'une case donnée est bien un portail.
//
extern "C" int api_portail_joueur(position portail)
{
  return api->portail_joueur(portail);
}

///
// Renvoie le nombre de boucliers présents sur un portail.
//
extern "C" int api_portail_boucliers(position portail)
{
  return api->portail_boucliers(portail);
}

///
// Renvoie la liste de tous les liens dont le portail donné est une extrémité.
//
extern "C" std::vector<lien> api_liens_incidents_portail(position portail)
{
  return api->liens_incidents_portail(portail);
}

///
// Renvoie la liste de tous les champs dont le portail donné est un sommet.
//
extern "C" std::vector<champ> api_champs_incidents_portail(position portail)
{
  return api->champs_incidents_portail(portail);
}

///
// Renvoie la liste de tous les champs dont le lien donné est un côté. Si le segment n'est pas un lien présent, renvoie la liste de tous les champs que la création du lien ferait apparaître.
//
extern "C" std::vector<champ> api_champs_incidents_segment(position ext1, position ext2)
{
  return api->champs_incidents_segment(ext1, ext2);
}

///
// Renvoie la liste des portails capturés par votre adversaire au dernier tour.
//
extern "C" std::vector<position> api_hist_portails_captures()
{
  return api->hist_portails_captures();
}

///
// Renvoie la liste des portails détruits par votre adversaire au dernier tour. Cela inclut toutes les utilisations de virus.
//
extern "C" std::vector<position> api_hist_portails_detruits()
{
  return api->hist_portails_detruits();
}

///
// Renvoie la liste des liens créés par votre adversaire au dernier tour.
//
extern "C" std::vector<position> api_hist_liens_crees()
{
  return api->hist_liens_crees();
}

///
// Renvoie la liste des champs créés par votre adversaire au dernier tour.
//
extern "C" std::vector<position> api_hist_champs_crees()
{
  return api->hist_champs_crees();
}

///
// Retourne la distance entre deux positions
//
extern "C" int api_distance(position pos1, position pos2)
{
  return api->distance(pos1, pos2);
}

///
// Renvoie le nombre de points que rapporte(rait) chaque tour un champ existant ou hypothétique.
//
extern "C" int api_score_triangle(position som1, position som2, position som3)
{
  return api->score_triangle(som1, som2, som3);
}

///
// Indique si deux segments se croisent. Cette fonction correspond exactement à la condition d'interférence entre liens, c'est-à-dire qu'elle renvoie ``false`` si l'intersection est une extrémité des deux segments.
//
extern "C" bool api_intersection_segments(position a1, position a2, position b1, position b2)
{
  return api->intersection_segments(a1, a2, b1, b2);
}

///
// Renvoie votre numéro de joueur.
//
extern "C" int api_moi()
{
  return api->moi();
}

///
// Renvoie le numéro de votre adversaire.
//
extern "C" int api_adversaire()
{
  return api->adversaire();
}

///
// Indique la position de l'agent du joueur désigné par le numéro ``id_joueur``.
//
extern "C" position api_position_agent(int id_joueur)
{
  return api->position_agent(id_joueur);
}

///
// Retourne le score du joueur désigné par le numéro ``id_joueur``.
//
extern "C" int api_score(int id_joueur)
{
  return api->score(id_joueur);
}

///
// Retourne le numéro du tour actuel.
//
extern "C" int api_tour_actuel()
{
  return api->tour_actuel();
}

///
// Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action à annuler ce tour-ci.
//
extern "C" bool api_annuler()
{
  return api->annuler();
}

///
// Affiche le contenu d'une valeur de type erreur
//
std::ostream& operator<<(std::ostream& os, erreur v)
{
  switch (v) {
  case OK: os << "OK"; break;
  case PA_INSUFFISANTS: os << "PA_INSUFFISANTS"; break;
  case AUCUN_PORTAIL: os << "AUCUN_PORTAIL"; break;
  case POSITION_INVALIDE: os << "POSITION_INVALIDE"; break;
  case POSITION_ELOIGNEE: os << "POSITION_ELOIGNEE"; break;
  case PORTAIL_AMI: os << "PORTAIL_AMI"; break;
  case PORTAIL_NEUTRE: os << "PORTAIL_NEUTRE"; break;
  case PORTAIL_ENNEMI: os << "PORTAIL_ENNEMI"; break;
  case LIEN_INTERSECTION: os << "LIEN_INTERSECTION"; break;
  case LIEN_CHAMP: os << "LIEN_CHAMP"; break;
  case LIMITE_BOUCLIERS: os << "LIMITE_BOUCLIERS"; break;
  }
  return os;
}
extern "C" void api_afficher_erreur(erreur v)
{
  std::cerr << v << std::endl;
}

///
// Affiche le contenu d'une valeur de type position
//
std::ostream& operator<<(std::ostream& os, position v)
{
  os << "{ ";
  os << "x" << "=" << v.x;
  os << ", ";
  os << "y" << "=" << v.y;
  os << " }";
  return os;
}
extern "C" void api_afficher_position(position v)
{
  std::cerr << v << std::endl;
}

///
// Affiche le contenu d'une valeur de type lien
//
std::ostream& operator<<(std::ostream& os, lien v)
{
  os << "{ ";
  os << "extr1" << "=" << v.extr1;
  os << ", ";
  os << "extr2" << "=" << v.extr2;
  os << ", ";
  os << "joueur" << "=" << v.joueur;
  os << " }";
  return os;
}
extern "C" void api_afficher_lien(lien v)
{
  std::cerr << v << std::endl;
}

///
// Affiche le contenu d'une valeur de type champ
//
std::ostream& operator<<(std::ostream& os, champ v)
{
  os << "{ ";
  os << "som1" << "=" << v.som1;
  os << ", ";
  os << "som2" << "=" << v.som2;
  os << ", ";
  os << "som3" << "=" << v.som3;
  os << ", ";
  os << "joueur" << "=" << v.joueur;
  os << " }";
  return os;
}
extern "C" void api_afficher_champ(champ v)
{
  std::cerr << v << std::endl;
}

