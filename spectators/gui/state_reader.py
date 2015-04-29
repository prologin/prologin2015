# -*- coding: utf-8 -*-

import ctypes
import json
import threading
import queue

from api import *

import game
import sys

class Reader:
    '''
    This class just exhibit the reader interface needed by the gui.
    A Reader object is used to get the game state with the source abstraction.
    '''

    def __init__(self):
        pass

    def get_previous_state(self):
        '''
        TODO
        Must only be called in the GUI thread.
        '''
        raise NotImplementedError()

    def go_previous(self):
        '''
        Prepare the Stechec client to go to the previous turn or raise a
        RuntimeError if this feature is not available.
        Must be called in the GUI thread.
        '''
        raise NotImplementedError()

    def get_next_state(self):
        '''
        Return if available the next game state.
        Must only be called in the GUI thread.
        '''
        raise NotImplementedError()

    def go_next(self):
        '''
        Prepare the Stechec client to go to the next turn.
        Must be called in the GUI thread.
        '''
        raise NotImplementedError()

    def put_state(self):
        '''
        Put the next game state.
        Must be called in the Stechec thread.
        '''
        raise NotImplementedError()

    def is_ended(self):
        '''
        Return if the game is ended.
        Must be called in the GUI thread.
        '''
        raise NotImplementedError()

    def wait_end(self):
        '''
        Wait the end of the game.
        Must be called in the GUI thread.
        '''
        raise NotImplementedError()

    def do_end(self):
        '''
        Make the game end.
        Must be called in the Stechec thread.
        '''
        raise NotImplementedError()

    def get_turn(self):
        '''
        Return the turn number.
        Should be called in the GUI thread.
        '''
        raise NotImplementedError()

    def build_state(self):
        '''
        Build a GameState object from the Stechec’s API and return it.
        Shouldn’t be called out of this class (Stechec thread).
        '''
        raise NotImplementedError()

    def can_quit(self):
        raise NotImplementedError()

    def can_go_backwards(self):
        raise NotImplementedError()

class StechecReader(Reader):
    '''
    Stechec reader get the game from the Stechec client.

    It must be used with two separated threads: one for the Stechec client, and
    one for the Gui. The Reader interface must be called only from the GUI
    thread, and the other methods only from the Stechec thread.
    '''

    def __init__(self):
        Reader.__init__(self)
        self.end_turn = threading.Event()
        self.pipe = queue.Queue()
        self.end_game = threading.Event()
        self.waiting_turn = False
        self.realeased = threading.Event()
        self.turn = 0
        self.waiting_end = threading.Event()

        librules = ctypes.cdll.LoadLibrary('libprologin2015.so')
        self.get_dump = librules.api_get_dump
        self.get_dump.argtypes = []
        self.get_dump.restype = ctypes.c_char_p

    def can_quit(self):
        return False

    def can_go_backwards(self):
        return False

    def go_previous(self):
        raise RuntimeError('Cannot get the previous state under Stechec')

    def get_next_state(self):
        if self.waiting_turn:
            return None
        game_state = None
        if not self.pipe.empty():
            self.turn += 1
            game_state = self.pipe.get()
            self.waiting_turn = True
        return game_state

    def go_next(self):
        if self.waiting_turn:
            self.waiting_turn = False
            self.end_turn.set()

    def put_state(self):
        if self.waiting_end.is_set():
            self.turn += 1
            # Flushing is used to delay the return of put_state. Yes, this is
            # an ugly hack.
            sys.stdin.flush()
            sys.stdout.flush()
            sys.stderr.flush()
            return
        game_state = self.build_state()
        self.pipe.put(game_state)
        self.end_turn.clear()
        self.end_turn.wait()

    def is_ended(self):
        return self.end_game.is_set()

    def wait_end(self):
        self.waiting_end.set()
        self.end_turn.set()

    def do_end(self):
        self.end_game.set()

    def get_turn(self):
        return self.turn

    def build_state(self):
        json_dump = self.get_dump().decode('ascii')
        result = game.GameState(json.loads(json_dump))
        self.turn += 1
        return result


class DumpReader(Reader):
    def __init__(self, dump_file):
        self.dump_file = dump_file

        # The current turn.
        self.turn = -1

        # A list of players (i.e. game.Player instances). Initialized from game
        # states each time one is decoded. This is used in TV show mode.
        self.players = None

        # For each turn, the file offset in `dump_file` to use when reading the
        # corresponding JSON dump. This is built lazyly as `go_next` is called.
        self.offsets = [0]

        self.is_ended_bool = False
        self.go_next()

    def can_quit(self):
        return True

    def can_go_backwards(self):
        return True

    def get_next_state(self):
        if self.next_state is not None:
            ns = self.next_state
            self.next_state = None
            return ns
        return None

    def go_next(self):
        self.next_state = self.read_state(+1)

        if self.turn == len(self.offsets) - 1:
            self.offsets.append(self.dump_file.tell())

    def get_previous_state(self):
        return self.get_next_state()

    def go_previous(self):
        self.next_state = self.read_state(-1)

    def read_state(self, offset):
        next_turn = max(0, self.turn + offset)
        self.dump_file.seek(self.offsets[next_turn])
        line = self.dump_file.readline()

        self.is_ended_bool = not line

        if self.is_ended_bool:
            return None
        else:
            self.turn = next_turn
            result = self.build_state(json.loads(line))
            self.players = result.players
            return result

    def is_ended(self):
        return self.is_ended_bool

    def get_turn(self):
        return self.turn

    def build_state(self, json):
        return game.GameState(json)
