#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import gzip
import sys

import pygame
import pygame.display
pygame.init()

import logs
import settings
from state_reader import DumpReader
from window import Window

settings.parser.add_argument('file', help='The file to replay')
settings.load(sys.argv[1:])

filename = settings.options.file

if filename.endswith('.gz'):
    dump_file = gzip.open(filename, 'rt')
else:
    dump_file = open(filename, 'r')
state_reader = DumpReader(dump_file)
window = Window(state_reader)
window.run()
