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
#include "panel-manager.h"
BUDGIE_END_PEDANTIC

G_DEFINE_TYPE(BudgiePanelManager, budgie_panel_manager, G_TYPE_OBJECT)

/**
 * budgie_panel_manager_dispose:
 *
 * Clean up a BudgiePanelManager instance
 */
static void budgie_panel_manager_dispose(GObject *obj)
{
        G_OBJECT_CLASS(budgie_panel_manager_parent_class)->dispose(obj);
}

/**
 * budgie_panel_manager_class_init:
 *
 * Handle class initialisation
 */
static void budgie_panel_manager_class_init(BudgiePanelManagerClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->dispose = budgie_panel_manager_dispose;
}

/**
 * budgie_panel_manager_init:
 *
 * Handle construction of the BudgiePanelManager
 */
static void budgie_panel_manager_init(__budgie_unused__ BudgiePanelManager *self)
{
}

BudgiePanelManager *budgie_panel_manager_new()
{
        return g_object_new(BUDGIE_TYPE_PANEL_MANAGER, NULL);
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
