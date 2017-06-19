# Provides budgie's main panel component

custom_target('desktop-file-panel',
    input : 'budgie-panel.desktop.in',
    output : 'budgie-panel.desktop',
    command : [intltool, '--desktop-style', podir, '@INPUT@', '@OUTPUT@'],
    install : true,
    install_dir : join_paths(datadir, 'applications'))

gresource = join_paths(meson.current_source_dir(), 'budgie-panel.gresource.xml')

# Compile the assets into the binary
panel_resources = gnome.compile_resources(
    'budgie-panel-resources',
    gresource,
    source_dir: meson.current_source_dir(),
    c_name: 'budgie_panel',
)

panel_sources = [
    'main.c',
    panel_resources,
]

panel_deps = [
    dep_gtk3,
    dep_peas,
    dep_libuuid,
    dep_wnck,
    link_libconfig,
    link_libsession,
    link_libtoplevel,
    link_libtheme,
    link_libplugin,
    link_libraven,
    gvc.get_variable('link_libgvc'),
]

top_vapidir = join_paths(meson.source_root(), 'vapi')

budgie_panel_c_args = [
    '-DWNCK_I_KNOW_THIS_IS_UNSTABLE'
]

# For popdown/popup methods
if dep_gtk322.found()
    budgie_panel_c_args += ['-D', 'HAVE_GTK_322']
endif

executable(
    'budgie-panel', panel_sources,
    dependencies: panel_deps,
    c_args: budgie_panel_c_args,
    install: true,
)

# gschemas
install_data(
    'com.solus-project.budgie-panel.gschema.xml',
    install_dir: join_paths(datadir, 'glib-2.0', 'schemas'),
)
