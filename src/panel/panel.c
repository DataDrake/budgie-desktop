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

#define _GNU_SOURCE

#include "util.h"

BUDGIE_BEGIN_PEDANTIC
#include "panel.h"
BUDGIE_END_PEDANTIC

G_DEFINE_TYPE(BudgiePanel, budgie_panel, GTK_TYPE_WINDOW)

/**
 * This is a hint to theme authors to provide a transparent definition,
 * as this is the background portion of the widget, not the main widget
 * itself.
 */
#define BUDGIE_STYLE_CONTAINER "budgie-container"

/**
 * budgie_panel_dispose:
 *
 * Clean up a BudgiePanel instance
 */
static void budgie_panel_dispose(GObject *obj)
{
        G_OBJECT_CLASS(budgie_panel_parent_class)->dispose(obj);
}

/**
 * budgie_panel_class_init:
 *
 * Handle class initialisation
 */
static void budgie_panel_class_init(BudgiePanelClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->dispose = budgie_panel_dispose;
}

/**
 * budgie_panel_init:
 *
 * Handle construction of the BudgiePanel
 */
static void budgie_panel_init(BudgiePanel *self)
{
        GtkStyleContext *style = NULL;

        style = gtk_widget_get_style_context(GTK_WIDGET(self));
        gtk_style_context_add_class(style, BUDGIE_STYLE_CONTAINER);

        /* Temporary */
        gtk_widget_show_all(GTK_WIDGET(self));
}

GtkWidget *budgie_panel_new()
{
        /*
         * Initialise all our default bits in batch
         * Blame clang-format for wrapping it like this
         */
        return g_object_new(BUDGIE_TYPE_PANEL,
                            "accept-focus",
                            FALSE,
                            "decorated",
                            FALSE,
                            "deletable",
                            FALSE,
                            "focus-on-map",
                            FALSE,
                            "resizable",
                            FALSE,
                            "skip-pager-hint",
                            TRUE,
                            "skip-taskbar-hint",
                            TRUE,
                            "type-hint",
                            GDK_WINDOW_TYPE_HINT_DOCK,
                            "type",
                            GTK_WINDOW_TOPLEVEL,
                            "window-position",
                            GTK_WIN_POS_NONE,
                            NULL);
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
