#! /usr/bin/env python2

import glob
import os.path


def options(opt):
    pass

def configure(cfg):
    pass

def build(bld):
    bld.shlib(
        source = '''
            src/action_ajouter_bouclier.cc
            src/action_capturer.cc
            src/action_deplacer.cc
            src/action_lier.cc
            src/action_neutraliser.cc
            src/action_utiliser_turbo.cc
            src/action_utiliser_virus.cc
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
        defines = ['MODULE_COLOR=ANSI_COL_BROWN', 'MODULE_NAME="rules"'],
        target = 'prologin2015',
        use = ['stechec2'],
    )

    abs_pattern = os.path.join(bld.path.abspath(), 'src/tests/test-*.cc')
    for test_src in glob.glob(abs_pattern):

        test_name = os.path.split(test_src)[-1]
        test_name = test_name[5:-3]

        # Waf requires a relative path for the source
        src_relpath = os.path.relpath(test_src, bld.path.abspath())

        bld.program(
            features = 'gtest',
            source = src_relpath,
            target = 'prologin2015-test-{}'.format(test_name),
            use = ['prologin2015', 'stechec2-utils'],
            includes = ['.'],
            defines = ['MODULE_COLOR=ANSI_COL_PURPLE',
                       'MODULE_NAME="prologin2015"'],
        )

    bld.install_files('${PREFIX}/share/stechec2/prologin2015', [
        'prologin2015.yml',
    ])
