# libtoplevel provides an in-tree ABI for Raven + Panel

# Generate enums for gobject typing
private_enums = gnome.mkenums(
    'budgie-private-enums',
    sources: 'applet.h',
    c_template: 'budgie-private-enums.c.template',
    h_template: 'budgie-private-enums.h.template',
    install_header: false,
)

# Fight meson race conditions..
libprivateenum = static_library(
    'privateenum',
    private_enums,
    dependencies: dep_gtk3,
)

link_libprivateenum = declare_dependency(
    sources: private_enums,
    include_directories: include_directories('.'),
)

libtoplevel_sources = [
    'animation.vala',
    'toplevel.vala',
    'shadow.vala',
    'manager.vala',
]

libtoplevel = static_library(
    'toplevel',
    libtoplevel_sources,
    dependencies: [
        link_libplugin,
        link_libprivateenum,
        dep_peas,
        dep_gtk3,
        meson.get_compiler('c').find_library('m', required: false),
    ],
    vala_args: [
        '--pkg', 'budgie-1.0',
        '--pkg', 'gio-unix-2.0',
        '--pkg', 'gtk+-3.0',
        '--pkg', 'libpeas-1.0',
        '--vapidir', dir_libplugin,
        '-H', 'BudgieToplevel.h',
    ],
)

link_libtoplevel = declare_dependency(
    link_with: libtoplevel,
    include_directories: [
        include_directories('.'),
    ],
)

# Expose the current directory so that we can use vapidir
dir_libtoplevel = meson.current_source_dir()
