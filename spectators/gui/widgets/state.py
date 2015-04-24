import pygame

import data
import data
import utils
from widgets.base import BaseWidget

# widget describing the state of the players
class StateWidget(BaseWidget):
    ICONS_PADDING = 3
    LEFT_MARGIN = data.GUI_ICON_WIDTH + ICONS_PADDING

    PADDING = 50
    LINE_HEIGHT = 70
    TEXT_SIZE = 12
    TEXT_HEIGHT = 15
    LINES = 12

    HEIGHT = TEXT_HEIGHT * LINES 
    def __init__(self, x, y, width):
        super(StateWidget, self).__init__(x, y, width, self.HEIGHT)
        self.font = pygame.font.Font(data.get_font_path('font.ttf'), self.TEXT_SIZE)
        self.game_state = None
        self.turn = 0
        self.last_turn = None

    def _display_text(self, text, height, color, column_info=None):
        '''
        Display a centered text at a given height, taking into account columns
        if any.
        '''
        if column_info:
            available_width = self.width - self.LEFT_MARGIN
            col_no, cols = column_info
            col_width = int(available_width / cols)
            col_start = self.LEFT_MARGIN + col_width * col_no
        else:
            col_start = 0
            col_width = self.width
        surf = self.font.render(text, True, color)
        surf_w, surf_h = surf.get_size()
        self.surface.blit(surf, (col_start + (col_width - surf_w) / 2, height))

    def _display_scores(self): # (And magic)
        if self.game_state is None:
            return
        players = self.game_state.players
        cols = len(players)
        for i, player in enumerate(players):
            self._display_text(
                player.name,
                0 * self.TEXT_HEIGHT,
                data.get_player_color(player),
                (i, cols)
            )
            self._display_text(
                str(player.score),
                1 * self.TEXT_HEIGHT,
                utils.WHITE,
                (i, cols)
            )

        # Put gui_icons in a left margin to explain the meaning of these
        # statistics.
        self.surface.blit(
            data.gui_icons['score'],
            (0, 1 * self.TEXT_HEIGHT)
        )

    def _display_turn(self):
        if self.last_turn:
            label = (
                u'Tour %d / %d' % (self.turn, self.last_turn)
                if self.turn <= self.last_turn else
                u'Fin de la partie'
            )
        else:
            label = u'Tour %d' % self.turn
        self._display_text(
            label, 4 * self.TEXT_HEIGHT, utils.WHITE
        )

    def _display_help(self):
        self._display_text(
            u'H: afficher/cacher l’aide', 8 * self.TEXT_HEIGHT, utils.WHITE
        )

    def _update(self):
        self.surface.fill(utils.BLACK)
        self._display_scores()
        self._display_turn()
        self._display_help()

    def update_turn(self, game_state):
        self.game_state = game_state
        self.turn = self.game_state.turn
        self.last_turn = self.game_state.turn_max
        self._update()

    def update_wait(self):
        self._update()
        self._display_text(u'Attente du prochain', 9 * self.TEXT_HEIGHT, utils.GREY)
        self._display_text(u'champion…', 10 * self.TEXT_HEIGHT, utils.GREY)

    def update_end(self):
        self._update()
        self._display_text(u'Match terminé', 9 * self.TEXT_HEIGHT, utils.GREY)

    def update_wait_end(self, turn):
        self.turn = turn
        self._update()
        self._display_text(u'Attente de la fin', 9 * self.TEXT_HEIGHT, utils.RED)
        self._display_text(u'du match', 10 * self.TEXT_HEIGHT, utils.RED)
