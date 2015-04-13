# -*- coding: utf-8 -*-

import inspect
import traceback

import api
from api import *


class Position:
    def __init__(self, *args):
        if len(args) == 1:
            arg = args[0]
            if isinstance(arg, tuple):
                self.x, self.y = arg
            else:
                self.x, self.y = arg.x, arg.y
        else:
            self.x, self.y = args

    def __add__(self, other):
        other = Position(other)
        return Position(self.x + other.x, self.y + other.y)

    def distance_to(self, other):
        other = Position(other)
        return abs(self.x - other.x) + abs(self.y - other.y)

    def closer_to(self, other):
        other = Position(other)
        if self.x > other.x:
            return Position(self.x - 1, self.y)
        elif self.x < other.x:
            return Position(self.x + 1, self.y)
        if self.y > other.y:
            return Position(self.x, self.y - 1)
        elif self.y < other.y:
            return Position(self,x, self.y + 1)
        else:
            raise ValueError('Cannot get any closer')

    @property
    def tuple(self):
        return (self.x, self.y)

    def __repr__(self):
        return 'Position({}, {})'.format(self.x, self.y)


class APIError(Exception):
    def __init__(self, action_repr, error):
        self.action_repr = action_repr
        self.error = error

    def __str__(self):
        return '{} returned {}'.format(
            self.action_repr,
            repr(self.error)
        )


def wrap_action(action_fn):
    def wrapper(self, *args):
        call_str = '{}({})'.format(action_fn.__name__,
                                   ', '.join(str(arg) for arg in args))
        print('-> {}'.format(call_str))
        try:
            result = erreur(action_fn(*args))
        except SystemError as exc:
            raise SystemError('{} raised a SystemError: {}'.format(
                call_str, exc
            ))
        if result != erreur.OK:
            raise APIError(call_str, result)
        return result
    return wrapper


class Game:

    def __init__(self):
        self.has_error = False
        self.gen_stack = [iter(self._play())]


    # Wrapped API

    @property
    def me(self):
        return moi()

    @property
    def him(self):
        return adversaire()

    def position(self, player_id):
        return Position(position_agent(player_id))

    def distance_to(self, pfrom, pto=None):
        pfrom = Position(pfrom)
        if not pto:
            pto = self.position(self.me)
        return pfrom.distance_to(pto)

    capturer = wrap_action(api.capturer)
    lier = wrap_action(api.lier)
    neutraliser = wrap_action(api.neutraliser)
    _deplacer = wrap_action(api.deplacer)
    ajouter_bouclier = wrap_action(api.ajouter_bouclier)
    utiliser_virus = wrap_action(api.utiliser_virus)
    utiliser_turbo = wrap_action(api.utiliser_turbo)

    def deplacer(self, pos):
        print('Deplacer: {} -> {}'.format(self.position(self.me), pos))
        pos = Position(pos)
        interm_pos = pos

        while True:
            start_pos = self.position(self.me)
            try:
                self._deplacer(interm_pos.tuple)
            except APIError as exc:
                if exc.error == erreur.POSITION_ELOIGNEE:
                    interm_pos = interm_pos.closer_to(start_pos)
                else:
                    raise
            else:
                if interm_pos == pos:
                    break
                else:
                    # We managed to move, but we're not there yet: in this case
                    # we are sure we cannot go further so wait for the next
                    # turn.
                    interm_pos = pos
                    yield False

            # If we tried to move just near current position, we need to wait
            # for the next turn.
            if interm_pos.distance_to(start_pos) == 0:
                interm_pos = pos
                yield False
        yield True


    def next(self):
        if self.has_error or not self.gen_stack:
            return

        print('=== Turn {} ==='.format(tour_actuel()))

        continue_playing = True
        while continue_playing:
            try:
                iter_yield = next(self.gen_stack[-1])
            except StopIteration:
                self.gen_stack.pop()
                continue_playing = bool(self.gen_stack)
                continue
            except:
                self.has_error = True
                with open('/tmp/log-{}'.format(self.me), 'a') as f:
                    traceback.print_exc(file=f)
                raise

            if inspect.isgenerator(iter_yield):
                self.gen_stack.append(iter_yield)
            else:
                continue_playing = bool(iter_yield)

    def _play(self):
        if position_agent(self.me) == (0, 0):
            portails = [(1, 1), (1, 4), (4, 1), (4, 4)]
        else:
            portails = [(38, 39), (28, 39), (35, 36)]

        for i, portail in enumerate(portails):
            yield from self.deplacer(portail)
            yield
            self.capturer()
            if i > 0:
                self.lier(portails[i - 1])
                self.ajouter_bouclier()

        yield
        yield self.deplacer(portails[-3])
        yield
        self.lier(portails[-1])
        self.ajouter_bouclier()


g = None


# Fonction appelée au début de la partie
def partie_init():
    global g
    g = Game()

# Fonction appelée à chaque tour
def jouer_tour():
    global g
    if not g:
        g = Game()
    g.next()

# Fonction appelée à la fin de la partie
def partie_fin():
    pass # Place ton code ici

