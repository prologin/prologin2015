#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright (c) 2012-2020 Association Prologin <association@prologin.org>

import glob
import os.path

from wafgenerator import generator_player_install


def options(opt):
    pass


def configure(cfg):
    pass


def build(bld):
    bld.shlib(
        source='''
            src/action_deplacer.cc
            src/action_utiliser_turbo.cc
            src/action_capturer.cc
            src/action_lier.cc
            src/action_neutraliser.cc
            src/action_ajouter_bouclier.cc
            src/api.cc
            src/dumper.cc
            src/entry.cc
            src/errors.cc
            src/game_state.cc
            src/geometry.cc
            src/graph.cc
            src/interface.cc
            src/map.cc
            src/rules.cc
        ''',
        defines=['MODULE_COLOR=ANSI_COL_BROWN', 'MODULE_NAME="rules"'],
        target='prologin2015',
        use=['stechec2'],
    )

    abs_pattern = os.path.join(bld.path.abspath(), 'src/tests/test-*.cc')
    for test_src in glob.glob(abs_pattern):

        test_name = os.path.split(test_src)[-1]
        test_name = test_name[len("test-"):-(len(".cc"))]

        # Waf requires a relative path for the source
        src_relpath = os.path.relpath(test_src, bld.path.abspath())

        bld.program(
            features='gtest',
            source=src_relpath,
            target='prologin2015-test-{}'.format(test_name),
            use=['prologin2015', 'stechec2-utils'],
            includes=['.'],
            defines=['MODULE_COLOR=ANSI_COL_PURPLE',
                     'MODULE_NAME="prologin2015"'],
        )

    bld.install_files('${PREFIX}/share/stechec2/prologin2015', [
        'prologin2015.yml',
    ])

    generator_player_install(bld, 'prologin2015')
