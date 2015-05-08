import pygame

import data
from game import area_x2
from utils import BLACK, WHITE, DARK_GREY
from widgets.base import BaseWidget

class PlayerStatWidget(BaseWidget):
    HEIGHT = 300
    PADDING = 8
    LINE_HEIGHT = 150

    def __init__(self, *args):
        self.font = pygame.font.Font(data.get_font_path('font.ttf'), 12)
        super(PlayerStatWidget, self).__init__(*args)

    def update_game(self, game):
        stats_per_player = {
            player.ui_id: { 'player': player, 'portals': 0, 'links': 0, 'fields': 0,
                            'area_x2': 0 }
            for player in game.players
        }
        for p1, p2, p3 in game.triangles:
            stats_per_player[p1.owner.ui_id]['fields'] += 1
            stats_per_player[p1.owner.ui_id]['area_x2'] += area_x2((p1,p2,p3))
        for p1, p2 in game.edges:
            stats_per_player[p1.owner.ui_id]['links'] += 1
        for portal in game.portals:
            if portal.owner:
                stats_per_player[portal.owner.ui_id]['portals'] += 1
                
        self.surface.fill(BLACK)
        for i, stats in enumerate(stats_per_player.values()):
            entry_y = self.PADDING + i * self.LINE_HEIGHT
            self._display_player_stats(stats['player'], stats, entry_y)

    def _display_player_stats(self, player, stats, entry_y):
        player_label = self.font.render(
            player.name,
            True, data.get_player_color(player)
        )
        self.surface.blit(
            player_label,
            (self.PADDING, entry_y)
        )

        score_label = self.font.render(
            "    Score = {0}".format(player.score),
            True, data.get_player_color(player)
        )
        area_label = self.font.render(
            "    Aire (x2) = {0}".format(stats['area_x2']),
            True, data.get_player_color(player)
        )

        self.surface.blit(
            score_label,
            (self.PADDING, entry_y + 3*self.PADDING)
        )
        self.surface.blit(
            area_label,
            (self.PADDING, entry_y + 7*self.PADDING)
        )


        left_shift = 2 * self.PADDING
        top_shift = entry_y + player_label.get_size()[1] + 10*self.PADDING
        remaining_width = self.width - left_shift - self.PADDING
        col_width = int(remaining_width / 3)
        text_space_w = col_width - data.ICON_WIDTH

        i = 0
        for item in 'portals links fields'.split():
            col_left = left_shift + i * col_width
            stat = stats[item]
            # Icon for the stat
            self.surface.blit(data.get_player_image(data.stats_icons[item], player),
                              (col_left, top_shift))
            if not stat:
                self.surface.blit(data.icon_shadow, (col_left, top_shift))
            # Numberic value
            text = self.font.render(
                str(stat), False,
                WHITE if stat else DARK_GREY
            )
            text_w, text_h = text.get_size()
            self.surface.blit(text, (
                col_left + data.ICON_WIDTH + (text_space_w - text_h) / 2,
                top_shift + (data.ICON_HEIGHT - text_h) / 2
            ))
            i += 1
