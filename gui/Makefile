# -*- Makefile -*-

lib_TARGETS = gui

gui-srcs = interface.cc
gui-dists = prologin.py api.py interface.hh

gui-cxxflags = -fPIC $(shell python3-config --includes)
gui-ldflags = -s $(shell python3-config --ldflags)

include ../includes/rules.mk
