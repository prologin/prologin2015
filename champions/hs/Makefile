# -*- Makefile -*-

lib_TARGETS = champion

# Tu peux rajouter des fichiers sources, headers, ou changer
# des flags de compilation.
champion-srcs = Prologin.hs
champion-dists = Prologin.hs

# Évite de toucher à ce qui suit
champion-dists += CApi.hsc Api.hs interface.hh interface_c.hh interface.cc
champion-srcs += CApi.hsc Api.hs interface.hh interface_c.hh interface.cc
champion-hsc-srcs = $(filter %.hsc,$(champion-srcs))
champion-hs-srcs = $(filter %.hs,$(champion-srcs)) $(champion-hsc-src:.hsc=.hs)

doc: $(champion-hs-srcs)
	haddock -o doc -t Prologin --package-name=Prologin -html --pretty-html $(champion-hs-srcs)

STECHEC_LANG = haskell
include ../includes/rules.mk
