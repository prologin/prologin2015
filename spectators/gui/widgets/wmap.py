from collections import defaultdict

import pygame
import pygame.draw

from api import *
import data
import game
import utils
from widgets.base import BaseWidget

class MapWidget(BaseWidget):

    WIDTH  = TAILLE_TERRAIN * data.TILE_WIDTH
    HEIGHT = TAILLE_TERRAIN * data.TILE_HEIGHT

    # Size of the text used to represent the number of shields on a portal.
    FONT_SIZE = 8

    def __init__(self, x, y):
        super(MapWidget, self).__init__(x, y, self.WIDTH, self.HEIGHT)

        # initializations
        self.game_state = None

        # Part of the map that does not change with the game state. This
        # basically just provides a background.
        self.static_map_surface = None

        # Rest of the map: agents, portals, edges and triangles.
        self.map_surface = None

        # Used only to display the number of shields on portals.
        self.font = pygame.font.Font(
            data.get_font_path('font.ttf'),
            self.FONT_SIZE
        )

    def plug(self, widgets):
        self.details_widget = widgets['details']

    def make_map_surface(self, game_state):
        surf_size = (
            game_state.map_width * data.TILE_WIDTH,
            game_state.map_height * (data.TILE_HEIGHT - data.TILE_OVERLAY) + data.TILE_OVERLAY
        )
        return utils.make_surface(*surf_size)

    def update_static_map(self, game_state=None):
        game_state = self.set_or_get_game_state(game_state)

        # Create the surface and paste "ground" tiles on it.
        self.static_map_surface = self.make_map_surface(game_state)
        for x in range(TAILLE_TERRAIN):
            for y in range(TAILLE_TERRAIN):
                # Alternate between two colors to display a grid.
                color = data.MAP_COLORS[(x + y) % 2]
                rect = (
                    x * data.TILE_WIDTH, y * data.TILE_HEIGHT,
                    data.TILE_WIDTH, data.TILE_HEIGHT
                )
                self.static_map_surface.fill(color, rect)

    def update_game(self, game_state=None):
        game_state = self.set_or_get_game_state(game_state)
        self.game_state = game_state
        #self.update_subjective(self.position)

        self.surface.fill(utils.BLACK)

        if self.game_state is None:
            return

        self.redraw_all()

    def coords(self, pos, shift=None):
        """Convert a map position into surface coordinates.

        If `shift` is not None, it must be a tuple used to shift the result
        pixel coordinates.
        """
        shift = shift or (0, 0)
        return (data.TILE_WIDTH * pos.x + shift[0],
                data.TILE_HEIGHT * pos.y + shift[1])

    def redraw_all(self):
        if self.map_surface is None:
            self.map_surface = self.make_map_surface(self.game_state)
        else:
            self.map_surface.fill((0, 0, 0, 0))

        if self.static_map_surface is None:
            self.update_static_map(self.game_state)

        # First draw lines and triangles: this is very noisy and we want the
        # rest on top of that.
        shift = (data.TILE_WIDTH / 2, data.TILE_HEIGHT / 2)
        for p1, p2, p3 in self.game_state.triangles:
            color = data.get_player_color(p1.owner) + (data.TRIANGLE_ALPHA, )
            pygame.draw.polygon(self.map_surface,
                                color,
                                [self.coords(p1.pos, shift),
                                 self.coords(p2.pos, shift),
                                 self.coords(p3.pos, shift)])
        for p1, p2 in self.game_state.edges:
            color = data.get_player_color(p1.owner) + (data.EDGE_ALPHA, )
            pygame.draw.line(self.map_surface,
                             color,
                             self.coords(p1.pos, shift),
                             self.coords(p2.pos, shift),
                             3)

        for portal in self.game_state.portals:
            coords = self.coords(portal.pos)
            self.map_surface.blit(
                data.get_player_image(data.portal_tiles, portal.owner),
                coords
            )
            if portal.shields > 0:
                self.map_surface.blit(data.tiles['shield'], coords)
                shields_count_text = utils.make_bordered_text(
                    str(portal.shields), self.font,
                    fgcolor=utils.WHITE
                )
                text_coords = self.coords(portal.pos, (
                    data.TILE_WIDTH - shields_count_text.get_size()[0],
                    0
                ))
                self.map_surface.blit(shields_count_text, text_coords)

        for player in self.game_state.players:
            self.map_surface.blit(
                data.get_player_image(data.player_tiles, player),
                self.coords(player.pos)
            )

        if False:
            coord_y = 0
            for y, row in enumerate(self.game_state.cells):
                coord_x = 0
                for x, cell in enumerate(row):
                    coords = (coord_x, coord_y)

                    # Add a tile on top of the static one for "dynamic" cells (such
                    # as towers).
                    if cell.type != case_info.CASE_SIMPLE:
                        tile = data.get_player_tile(
                            cell.type, self.game_state, cell.object_player
                        )
                        self.map_surface.blit(tile, coords)

                    # Likewise for wizards.
                    if cell.wizards > 0:
                        # The wizard tiles should be drawed only on simple cells.
                        # Other tiles (base, fountains, towers, artefacts) already
                        # contain the player color, so don't put too many tiles on
                        # the same cell: only put the wizard count in such cases.
                        if cell.type == case_info.CASE_SIMPLE:
                            wizard_tile = data.get_player_image(
                                data.wizards, self.game_state, cell.wizards_player
                            )
                            self.map_surface.blit(wizard_tile, coords)

                        count_text = utils.make_bordered_text(
                            str(cell.wizards), self.font,
                            fgcolor=data.get_player_color(
                                self.game_state, cell.wizards_player
                            )
                        )
                        count_width, count_height = count_text.get_size()
                        self.map_surface.blit(count_text, (
                            coord_x + data.TILE_WIDTH - count_width,
                            coord_y
                        ))

                    coord_x += data.TILE_WIDTH
                coord_y += data.TILE_HEIGHT - data.TILE_OVERLAY

        # update display
        self.surface.fill(utils.BLACK)
        self.surface.blit(self.static_map_surface, (0, 0))
        self.surface.blit(self.map_surface, (0, 0))

    def set_or_get_game_state(self, game_state=None):
        if game_state:
            self.game_state = game_state
        return self.game_state
