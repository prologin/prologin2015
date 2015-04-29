import threading

import pygame

# initialization
pygame.init()

import state_reader
import window
import settings

settings.load([])

game_state_reader = state_reader.StechecReader()
window = window.Window(game_state_reader)
gfx_thread = threading.Thread(target=window.run)

def partie_init():
    gfx_thread.start()

def jouer_tour():
    game_state_reader.put_state()

def partie_fin():
    game_state_reader.do_end()
