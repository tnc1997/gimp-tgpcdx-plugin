project(
    'gimp_tgpcdx_plugin',
    'c',
    default_options: ['c_std=c11'],
    license: 'MIT',
    meson_version: '>=0.58.0',
    version: '1.0.0',
)

gimp_dep = dependency('gimp-2.0')
gimpui_dep = dependency('gimpui-2.0')

executable(
    'file-tgpcdx',
    'main.c',
    dependencies: [gimp_dep, gimpui_dep],
    install: true,
    install_dir: gimp_dep.get_variable('gimplibdir') / 'plug-ins' / 'file-tgpcdx',
)
