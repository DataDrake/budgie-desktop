/*
 * This file is part of budgie-desktop
 *
 * Copyright © 2015-2017 Ikey Doherty <ikey@solus-project.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "config.h"
#include "util.h"

BUDGIE_BEGIN_PEDANTIC
#include <glib/gi18n.h>
#include <gtk/gtk.h>
BUDGIE_END_PEDANTIC

#include <stdlib.h>

DEF_AUTOFREE(GOptionContext, g_option_context_free)
DEF_AUTOFREE(GError, g_error_free)
DEF_AUTOFREE(gchar, g_free)

static gboolean replace = FALSE;
static gboolean reset_manager = FALSE;

/**
 * TODO: Make this translatable and pass GETTEXT_PACKAGE to _add_main_entries
 */
static const GOptionEntry option_entries[] =
    { { "replace", 0, 0, G_OPTION_ARG_NONE, &replace, "Replace currently running panel", NULL },
      { "reset", 0, 0, G_OPTION_ARG_NONE, &reset_manager, "Reset the panel configuration", NULL },
      { NULL } };

int main(int argc, char **argv)
{
        autofree(GOptionContext) *context = NULL;
        autofree(GError) *error = NULL;

        /* Hook up locales */
        setlocale(LC_ALL, "");
        bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
        bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
        textdomain(GETTEXT_PACKAGE);

        /* Hook up CLI options */
        context = g_option_context_new("- Budgie Panel");
        g_option_context_set_help_enabled(context, TRUE);
        g_option_context_add_main_entries(context, option_entries, NULL);
        g_option_context_add_group(context, gtk_get_option_group(FALSE));

        if (!g_option_context_parse(context, &argc, &argv, &error)) {
                autofree(gchar) *txt = g_option_context_get_help(context, TRUE, NULL);
                fprintf(stderr, "%s: %s\n\n%s", argv[0], error->message, txt);
                return EXIT_FAILURE;
        }

        /* TODO: Stuff a budgie_panel_manager_new here
        gtk_main(); */

        return EXIT_SUCCESS;
}
