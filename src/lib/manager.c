/*
 * This file is part of budgie-desktop.
 *
 * Copyright © 2015-2017 Ikey Doherty <ikey@solus-project.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#define _GNU_SOURCE

#include "util.h"

BUDGIE_BEGIN_PEDANTIC
#include "manager.h"
BUDGIE_END_PEDANTIC

/**
 * IDs for our signals
 */
enum { MANAGER_SIGNAL_PANELS_CHANGED = 0,
       N_SIGNALS };

static guint manager_signals[N_SIGNALS] = { 0 };

G_DEFINE_ABSTRACT_TYPE(BudgieDesktopManager, budgie_desktop_manager, G_TYPE_OBJECT)

/**
 * budgie_desktop_manager_dispose:
 *
 * Clean up a BudgieDesktopManager instance
 */
static void budgie_desktop_manager_dispose(GObject *obj)
{
        G_OBJECT_CLASS(budgie_desktop_manager_parent_class)->dispose(obj);
}

/**
 * budgie_desktop_manager_class_init:
 *
 * Handle class initialisation
 */
static void budgie_desktop_manager_class_init(BudgieDesktopManagerClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->dispose = budgie_desktop_manager_dispose;

        /**
         * BudgieDesktopManager::panels-changed
         * @self: The desktop manager emitting the signal
         *
         * Used to notify interested parties that panels have updated
         */
        manager_signals[MANAGER_SIGNAL_PANELS_CHANGED] =
            g_signal_new("panels-changed",
                         BUDGIE_TYPE_DESKTOP_MANAGER,
                         G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION,
                         G_STRUCT_OFFSET(BudgieDesktopManager, panels_changed),
                         NULL,
                         NULL,
                         NULL,
                         G_TYPE_NONE,
                         0);
}

GList *budgie_desktop_manager_get_panels(BudgieDesktopManager *self)
{
        BudgieDesktopManager *klazz = BUDGIE_DESKTOP_MANAGER_GET_CLASS(self);
        g_assert(klazz->get_panels != NULL);
        return klazz->get_panels(self);
}

guint budgie_desktop_manager_slots_available(BudgieDesktopManager *self)
{
        BudgieDesktopManager *klazz = BUDGIE_DESKTOP_MANAGER_GET_CLASS(self);
        g_assert(klazz->slots_available != NULL);
        return klazz->slots_available(self);
}

guint budgie_desktop_manager_slots_available(BudgieDesktopManager *self)
{
        BudgieDesktopManager *klazz = BUDGIE_DESKTOP_MANAGER_GET_CLASS(self);
        g_assert(klazz->slots_used != NULL);
        return klazz->slots_used(self);
}

void budgie_desktop_manager_set_placement(BudgieDesktopManager *self, const gchar *uuid, BudgiePanelPosition position)
{
        BudgieDesktopManager *klazz = BUDGIE_DESKTOP_MANAGER_GET_CLASS(self);
        g_assert(klazz->set_placement != NULL);
        klazz->set_placement(self, uuid, position);
}

void budgie_desktop_manager_set_transparency(BudgieDesktopManager *self, const gchar *uuid, BudgiePanelTransparency transparency)
{
        BudgieDesktopManager *klazz = BUDGIE_DESKTOP_MANAGER_GET_CLASS(self);
        g_assert(klazz->set_transparency != NULL);
        klazz->set_transparency(self, uuid, transparency);
}

void budgie_desktop_manager_set_size(BudgieDesktopManager *self, const gchar *uuid, gint new_size)
{
        BudgieDesktopManager *klazz = BUDGIE_DESKTOP_MANAGER_GET_CLASS(self);
        g_assert(klazz->set_size != NULL);
        klazz->set_size(self, uuid, size);
}

void budgie_desktop_manager_create_new_panel(BudgieDesktopManager *self)
{
        BudgieDesktopManager *klazz = BUDGIE_DESKTOP_MANAGER_GET_CLASS(self);
        g_assert(klazz->create_new_panel != NULL);
        klazz->create_new_panel(self);
}

void budgie_desktop_manager_delete_panel(BudgieDesktopManager *self, const gchar *uuid)
{
        BudgieDesktopManager *klazz = BUDGIE_DESKTOP_MANAGER_GET_CLASS(self);
        g_assert(klazz->delete_panel != NULL);
        klazz->delete_panel(self, uuid);
}

GList *budgie_desktop_manager_get_panel_plugins(BudgieDesktopManager *self)
{
        BudgieDesktopManager *klazz = BUDGIE_DESKTOP_MANAGER_GET_CLASS(self);
        g_assert(klazz->get_panel_plugins != NULL);
        return klazz->get_panel_plugins(self);
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
