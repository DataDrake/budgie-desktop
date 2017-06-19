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

G_DEFINE_TYPE(BudgiePanel, budgie_panel, G_TYPE_OBJECT)

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
static void budgie_panel_init(__budgie_unused__ BudgiePanel *self)
{
}

GtkWidget *budgie_panel_new()
{
        return g_object_new(BUDGIE_TYPE_PANEL, NULL);
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
