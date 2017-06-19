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

#pragma once

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

/**
 * BudgiePanelPosition:
 * @BUDGIE_PANEL_POSITION_NONE: Currently has no position
 * @BUDGIE_PANEL_POSITION_BOTTOM: Panel owns the bottom edge
 * @BUDGIE_PANEL_POSITION_TOP: Panel owns the top edge
 * @BUDGIE_PANEL_POSITION_LEFT: Panel owns the left edge
 * @BUDGIE_PANEL_POSITION_RIGHT: Panel owns the right edge
 *
 * BudgiePanelPosition determins a panel's position on the screen.
 */
typedef enum {
        BUDGIE_PANEL_POSITION_NONE = 1 << 0,
        BUDGIE_PANEL_POSITION_BOTTOM = 1 << 1,
        BUDGIE_PANEL_POSITION_TOP = 1 << 2,
        BUDGIE_PANEL_POSITION_LEFT = 1 << 3,
        BUDGIE_PANEL_POSITION_RIGHT = 1 << 4,
} BudgiePanelPosition;

/**
 * BudgiePanelTransparency:
 * @BUDGIE_PANEL_TRANSPARENCY_NONE: Do not use any transparency
 * @BUDGIE_PANEL_TRANSPARENCY_DYNAMIC: Dynamically set transparency
 * @BUDGIE_PANEL_TRANSPARENCY_ALWAYS: Always use transparency
 *
 * BudgiePanelTransparency controls the transparency setting for a panel,
 * allowing each panel to control whether it uses an alpha mode, and under
 * which circumstance it is appropriate to do this.
 */
typedef enum {
        BUDGIE_PANEL_TRANSPARENCY_NONE = 1 << 0,
        BUDGIE_PANEL_TRANSPARENCY_DYNAMIC = 1 << 1,
        BUDGIE_PANEL_TRANSPARENCY_ALWAYS = 1 << 2,
} BudgiePanelTransparency;

typedef struct _BudgieToplevel BudgieToplevel;
typedef struct _BudgieToplevelClass BudgieToplevelClass;
typedef struct _BudgieToplevelPrivate BudgieToplevelPrivate;
    
struct _BudgieToplevelClass {
        GtkWindowClass parent_class;

        void (*reset_shadow)(BudgieToplevel *);
        GList *(*get_applets)(BudgieToplevel *);

        /* Signals */
        void (*applet_added)(BudgieToplevel *, BudgieAppletInfo *);
        void (*applet_removed)(BudgieToplevel *, BudgieAppletInfo *);
        void (*applets_changed)(BudgieToplevel *);

        /* Mover functions */
        gboolean (*can_move_applet_left)(BudgieToplevel *, BudgieAppletInfo *);
        gboolean (*can_move_applet_right)(BudgieToplevel *, BudgieAppletInfo *);
        void (*move_applet_left)(BudgieToplevel *, BudgieAppletInfo *);
        void (*move_applet_right)(BudgieToplevel *, BudgieAppletInfo *);

        /* Lifecycle */
        void (*add_new_applet)(BudgieToplevel *, const gchar *id);
        void (*remove_applet)(BudgieToplevel *, BudgieAppletInfo *);
};

/**
 * BudgieToplevel is an abstract type that hides the details of management
 * of panels and regions, used between the PanelManager, Raven and BudgiePanel
 */
struct _BudgieToplevel {
        GtkWindow parent;
        BudgieToplevelPrivate *priv;
};

#define BUDGIE_TYPE_TOPLEVEL budgie_toplevel_get_type()
#define BUDGIE_TOPLEVEL(o) (G_TYPE_CHECK_INSTANCE_CAST((o), BUDGIE_TYPE_TOPLEVEL, BudgieToplevel))
#define BUDGIE_IS_TOPLEVEL(o) (G_TYPE_CHECK_INSTANCE_TYPE((o), BUDGIE_TYPE_TOPLEVEL))
#define BUDGIE_TOPLEVEL_CLASS(o) (G_TYPE_CHECK_CLASS_CAST((o), BUDGIE_TYPE_TOPLEVEL, BudgieToplevelClass))
#define BUDGIE_IS_TOPLEVEL_CLASS(o) (G_TYPE_CHECK_CLASS_TYPE((o), BUDGIE_TYPE_TOPLEVEL))
#define BUDGIE_TOPLEVEL_GET_CLASS(o)                                                                  \
        (G_TYPE_INSTANCE_GET_CLASS((o), BUDGIE_TYPE_TOPLEVEL, BudgieToplevelClass))

GType budgie_toplevel_get_type(void);

/** API Methods */
void budgie_toplevel_reset_shadow(BudgieToplevel *self);
GList *budgie_toplevel_get_applets(BudgieToplevel *self);

gboolean budgie_toplevel_can_move_applet_left(BudgieToplevel *self, BudgieAppletInfo *info);
gboolean budgie_toplevel_can_move_applet_right(BudgieToplevel *self, BudgieAppletInfo *info);
void budgie_toplevel_move_applet_left(BudgieToplevel *self, BudgieAppletInfo *info);
void budgie_toplevel_move_applet_right(BudgieToplevel *self, BudgieAppletInfo *info);

void budgie_toplevel_add_new_applet(BudgieToplevel *self, const gchar *id);
void budgie_toplevel_remove_applet(BudgieToplevel *self, BudgieAppletInfo *info);

G_END_DECLS

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
