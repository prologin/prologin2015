#! /usr/bin/env python2

def options(opt):
    pass

def configure(cfg):
    pass

def build(bld):
    bld.shlib(
        source = '''
            src/action_ajouter_bouclier.cc
            src/action_capturer.cc
            src/action_detruire.cc
            src/action_deplacer.cc
            src/action_lier.cc
            src/action_utiliser_turbo.cc
            src/action_utiliser_virus.cc
            src/api.cc
            src/entry.cc
            src/game_state.cc
            src/interface.cc
            src/map.cc
            src/rules.cc
        ''',
        defines = ['MODULE_COLOR=ANSI_COL_BROWN', 'MODULE_NAME="rules"'],
        target = 'prologin2015',
        use = ['stechec2'],
    )

    bld.install_files('${PREFIX}/share/stechec2/prologin2015', [
        'prologin2015.yml',
    ])
