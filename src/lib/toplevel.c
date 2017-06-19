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
#include "toplevel.h"
BUDGIE_END_PEDANTIC

/**
 * IDs for our signals
 */
enum { TOPLEVEL_SIGNAL_APPLET_ADDED = 0,
enum { TOPLEVEL_SIGNAL_APPLET_REMOVED = 0,
enum { TOPLEVEL_SIGNAL_APPLETS_CHANGED = 0,
       N_SIGNALS };

static guint toplevel_signals[N_SIGNALS] = { 0 };

struct _BudgieToplevelPrivate {
        gint shadow_width;
        gint shadow_depth;
        gint intended_size;
        gboolean shadow_visible;
        gboolean theme_regions;
}

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE(BudgieToplevel, budgie_toplevel, GTK_TYPE_WINDOW)

static void budgie_toplevel_set_property(GObject *object, guint id, const GValue *value,
                                         GParamSpec *spec)
{
        BudgieToplevel *self = BUDGIE_TOPLEVEL(object);

        switch (id) {
        case PROP_INFO:
                self->info = g_value_dup_object(value);
                break;
        case PROP_SECTION_ID:
                g_clear_pointer(&self->section_id, g_free);
                self->section_id = g_value_dup_string(value);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, spec);
                break;
        }
}

static void budgie_toplevel_get_property(GObject *object, guint id, GValue *value, GParamSpec *spec)
{
        BudgieToplevel *self = BUDGIE_TOPLEVEL(object);

        switch (id) {
        case PROP_INFO:
                g_value_set_pointer(value, self->info);
                break;
        case PROP_SECTION_ID:
                g_value_set_string(value, self->section_id);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, spec);
                break;
        }
}

/**
 * budgie_toplevel_dispose:
 *
 * Clean up a BudgieToplevel instance
 */
static void budgie_toplevel_dispose(GObject *obj)
{
        G_OBJECT_CLASS(budgie_toplevel_parent_class)->dispose(obj);
}

/**
 * budgie_toplevel_class_init:
 *
 * Handle class initialisation
 */
static void budgie_toplevel_class_init(BudgieToplevelClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->dispose = budgie_toplevel_dispose;

        /**
         * BudgieToplevel::applet-added
         * @self: The backend that created the applet
         * @applet: The newly available applet
         *
         * Notify interested parties that an applet was added
         */
        backend_signals[TOPLEVEL_SIGNAL_APPLET_ADDED] =
            g_signal_new("applet-added",
                         BUDGIE_TYPE_TOPLEVEL,
                         G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION,
                         G_STRUCT_OFFSET(BudgieToplevelClass, applet_added),
                         NULL,
                         NULL,
                         NULL,
                         G_TYPE_NONE,
                         1,
                         BUDGIE_TYPE_APPLET_INFO);

        /**
         * BudgieToplevel::applet-removed
         * @self: The toplevel that removed the applet
         * @applet: The applet that is being removed
         *
         * Notify interested parties that an applet was removed
         */
        backend_signals[TOPLEVEL_SIGNAL_APPLET_REMOVED] =
            g_signal_new("applet-removed",
                         BUDGIE_TYPE_TOPLEVEL,
                         G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION,
                         G_STRUCT_OFFSET(BudgieToplevelClass, applet_removed),
                         NULL,
                         NULL,
                         NULL,
                         G_TYPE_NONE,
                         1,
                         BUDGIE_TYPE_APPLET_INFO);

        /**
         * BudgieToplevel::applets-changed
         * @self: The toplevel emitting the signal
         *
         * Used to notify interested parties that applets have updated
         */
        manager_signals[TOPLEVEL_SIGNAL_APPLETS_CHANGED] =
            g_signal_new("applets-changed",
                         BUDGIE_TYPE_TOPLEVEL,
                         G_SIGNAL_RUN_LAST | G_SIGNAL_ACTION,
                         G_STRUCT_OFFSET(BudgieToplevel, applets_changed),
                         NULL,
                         NULL,
                         NULL,
                         G_TYPE_NONE,
                         0);
}

void budgie_toplevel_reset_shadow(BudgieToplevel *self)
{
        BudgieToplevelClass *klazz = BUDGIE_TOPLEVEL_GET_CLASS(self);
        g_assert(klazz->reset_shadow != NULL);
        klazz->reset_shadow(self);
}

GList *budgie_toplevel_get_applets(BudgieToplevel *self)
{
        BudgieToplevelClass *klazz = BUDGIE_TOPLEVEL_GET_CLASS(self);
        g_assert(klazz->get_applets != NULL);
        return klazz->get_applets(self);
}

gboolean budgie_toplevel_can_move_applet_left(BudgieToplevel *self, BudgieAppletInfo *info)
{
        BudgieToplevelClass *klazz = BUDGIE_TOPLEVEL_GET_CLASS(self);
        g_assert(klazz->can_move_applet_left != NULL);
        return klazz->can_move_applet_left(self);
}

gboolean budgie_toplevel_can_move_applet_right(BudgieToplevel *self, BudgieAppletInfo *info)
{
        BudgieToplevelClass *klazz = BUDGIE_TOPLEVEL_GET_CLASS(self);
        g_assert(klazz->can_move_applet_right != NULL);
        return klazz->can_move_applet_right(self);
}

void budgie_toplevel_move_applet_left(BudgieToplevel *self, BudgieAppletInfo *info)
{
        BudgieToplevelClass *klazz = BUDGIE_TOPLEVEL_GET_CLASS(self);
        g_assert(klazz->move_applet_left != NULL);
        klazz->move_applet_left(self);
}

void budgie_toplevel_move_applet_right(BudgieToplevel *self, BudgieAppletInfo *info)
{
        BudgieToplevelClass *klazz = BUDGIE_TOPLEVEL_GET_CLASS(self);
        g_assert(klazz->move_applet_right != NULL);
        klazz->move_applet_right(self);
}

void budgie_toplevel_add_new_applet(BudgieToplevel *self, const gchar *id)
{
        BudgieToplevelClass *klazz = BUDGIE_TOPLEVEL_GET_CLASS(self);
        g_assert(klazz->add_new_applet != NULL);
        klazz->add_new_applet(self);
}

void budgie_toplevel_remove_applet(BudgieToplevel *self, BudgieAppletInfo *info)
{
        BudgieToplevelClass *klazz = BUDGIE_TOPLEVEL_GET_CLASS(self);
        g_assert(klazz->remove_applet != NULL);
        klazz->remove_applet(self);
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
