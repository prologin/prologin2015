import pygame

import data
from utils import WHITE, make_surface
from widgets.base import BaseWidget


def center(wide_size, tiny_size):
    return (wide_size - tiny_size) // 2


class TVShowWidget(BaseWidget):
    """
    Widget used in the TV show mode. It can display two screens:
        - "Champion 1 vs. Champion2"
        - Final scores

    This is useful to display matches in batch.
    """

    #
    # Font sizes
    #

    TEXT_SIZE = 30
    CHAMPION_SIZE = 40
    PADDING = 70

    #
    # Timing settings
    #

    # Duration (in seconds) for the initial screen
    INIT_DURATION = 5

    # Duration (in seconds) for the final screen
    FINI_DURATION = 5

    def __init__(self, width, height):
        super(TVShowWidget, self).__init__(0, 0, width, height)
        self.enabled = False

    def __enter__(self):
        self.enabled = True

    def __exit__(self, exc, exc_type, traceback):
        self.enabled = False

    def create_init(self, players):
        self._render(players, False)

    def create_fini(self, players):
        self._render(players, True)

    def _get_font(self, size):
        return pygame.font.Font(data.get_font_path('font.ttf'), size)

    def _render(self, players, use_scores):
        assert len(players) == 2
        self.surface.fill((0, 0, 0, 160))

        p1_label = self._render_player_name(
            players[0], use_scores,
            players[0].score > players[1].score
        )
        p2_label = self._render_player_name(
            players[1], use_scores,
            players[0].score < players[1].score
        )
        vs_label = self._get_font(self.TEXT_SIZE).render('vs.', True, WHITE)

        p1_w, p1_h = p1_label.get_size()
        p2_w, p2_h = p2_label.get_size()
        vs_w, vs_h = vs_label.get_size()

        total_height = p1_h + p2_h + vs_h + 2 * self.PADDING

        y = center(self.height, total_height)
        self.surface.blit(p1_label, (center(self.width, p1_w), y))
        y += p1_h + self.PADDING

        self.surface.blit(vs_label, (center(self.width, vs_w), y))
        y += vs_h + self.PADDING

        self.surface.blit(p2_label, (center(self.width, p2_w), y))

    def _render_player_name(self, player, use_scores, has_won):

        def get_size(base):
            return int(base * 2.5) if has_won else base

        raw_label = self._get_font(get_size(self.CHAMPION_SIZE)).render(
            player.name, True, data.PLAYER_COLORS[player.ui_id])
        if not use_scores:
            return raw_label

        score_label = self._get_font(get_size(self.CHAMPION_SIZE)).render(
            '{} points'.format(player.score), True, WHITE)

        raw_w, raw_h = raw_label.get_size()
        score_w, score_h = score_label.get_size()
        score_y = raw_h

        result = make_surface(
            max(raw_w, score_w),
            score_y + score_h
        )
        result.blit(raw_label, (0, 0))
        result.blit(score_label,
                    (center(result.get_size()[0], score_w), score_y))
        return result
