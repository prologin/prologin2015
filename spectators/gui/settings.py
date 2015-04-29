import argparse

import utils

parser = argparse.ArgumentParser()
parser.add_argument(
    '-F', '--fullscreen', action='store_true', help='Fullscreen mode'
)
parser.add_argument(
    '-S', '--tv-show', action='store_true',
    help='Enables the TV show mode: display special screens and run everything'
         ' automatically (including stopping the main loop at the end)'
)

options = None

def load(argv):
    global options
    options = parser.parse_args(argv)
