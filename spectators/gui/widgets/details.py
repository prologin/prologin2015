import pygame

import data
from utils import BLACK, WHITE
from widgets.base import BaseWidget

class DetailsWidget(BaseWidget):

    def __init__(self, *args):
        self.font = pygame.font.Font(data.get_font_path('font.ttf'), 12)
        super(DetailsWidget, self).__init__(*args)

    def update_position(self, x, y):
        self.surface.fill(BLACK)
        label = self.font.render('(x={}, y={})'.format(x, y), True, WHITE)
        self.surface.blit(label, (0, 0))
