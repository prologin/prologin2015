# -*- Makefile -*-

lib_TARGETS = champion

# Tu peux rajouter des fichiers .ml ou changer les flags de ocamlc
# Les fichiers .mli correspondants seront automatiquement utilises si
# existants.
champion-srcs = api.ml prologin.ml
# lolhack
# TODO: find a place to add .cma files to linking command instead
champion-camlflags = str.cma bigarray.cma nums.cma unix.cma batteries.cma -g -I /usr/lib/ocaml/batteries/

# Evite de toucher a ce qui suit
champion-dists = interface.hh
champion-srcs += interface.cc
STECHEC_LANG=caml
include ../includes/rules.mk
