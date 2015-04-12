import os.path
import re

import pygame

from api import *
import game
import utils


TILE_WIDTH = 20
TILE_HEIGHT = 20
TILE_OVERLAY = 0
GUI_ICON_WIDTH = 12
GUI_ICON_HEIGHT = 12
ICON_WIDTH = 32
ICON_HEIGHT = 32


EDGE_ALPHA = 160
TRIANGLE_ALPHA = 100


MAP_COLORS = [
    (0, ) * 3,
    (16, ) * 3,
]


NO_PLAYER_COLOR = (128, 128, 128)
PLAYER_COLORS = [
    (64, 128, 192),
    (192, 64, 64),
    (48, 192, 64),
    (234, 192, 64),
]

ColoredImages = namedtuple('ColoredImages', 'no_player players')

images_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'data')

def get_image_path(name):
    return os.path.join(images_dir, name)

def get_images(names):
    result = {}
    for name in names:
        path = get_image_path('{}.png'.format(name))
        img = pygame.image.load(path).convert_alpha()
        result[name] = img
    return result

def load_images():
    global gui_icons, tiles
    global player_tiles
    global portal_tiles

    gui_icons = get_images(['score'])
    tiles = get_images('portal shield player1 player2'.split())

    portal_tiles = get_colored_images(tiles['portal'],
                                      lambda c: utils.lighter(c, 0.25))
    player_tiles = ColoredImages(None, [
        utils.set_color(tiles['player1'], PLAYER_COLORS[0]),
        utils.set_color(tiles['player2'], PLAYER_COLORS[1]),
    ])

def get_font_path(name):
    return os.path.join(images_dir, name)

def get_player_image(images, player):
    if player is None:
        return images.no_player
    else:
        return images.players[player.ui_id]

def get_player_color(player, filter=None):
    result = NO_PLAYER_COLOR if player is None else PLAYER_COLORS[player.ui_id]
    if filter:
        result = filter(result)
    return result

def get_colored_images(pattern, color_filter=None):
    color_filter = color_filter or (lambda c: c)
    return ColoredImages(
        utils.set_color(pattern, color_filter(NO_PLAYER_COLOR)),
        [
            utils.set_color(pattern, color_filter(color))
            for color in PLAYER_COLORS
        ]
    )
