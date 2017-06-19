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

G_BEGIN_DECLS

typedef struct _BudgieDesktopManager BudgieDesktopManager;
typedef struct _BudgieDesktopManagerClass BudgieDesktopManagerClass;

struct _BudgieDesktopManagerClass {
        GObjectClass parent_class;

        /* Signal */
        void (*panels_changed)(BudgieDesktopManager *);

        /* Accessor method */
        GList *(*get_panels)(BudgieDesktopManager *);

        /* Slot queries */
        guint (*slots_available)(BudgieDesktopManager *)
        guint (*slots_used)(BudgieDesktopManager *)

        /* Per panel settings */
        void (*set_placement)(BudgieDesktopManager *, const gchar *, BudgiePanelPosition);
        void (*set_transparency)(BudgieDesktopManager *, const gchar *, BudgiePanelTransparency);
        void (*set_size)(BudgieDesktopManager *, const gchar *, gint);

        /* Life cycle methods */
        void (*create_new_panel)(BudgieDesktopManager *);
        void (*delete_panel)(BudgieDesktopManager *, const gchar *);

        /* Engine method */
        GList *(*get_panel_plugins)(BudgieDesktopManager *);

        /* ABI break from Vala version */
        gpointer padding[12];
};

/**
 * BudgieDesktopManager is an abstract type that hides the details of management
 * of panels and regions, used between the PanelManager, Raven and BudgiePanel
 */
struct _BudgieDesktopManager {
        GObject parent;
};

#define BUDGIE_TYPE_DESKTOP_MANAGER budgie_desktop_manager_get_type()
#define BUDGIE_DESKTOP_MANAGER(o) (G_TYPE_CHECK_INSTANCE_CAST((o), BUDGIE_TYPE_DESKTOP_MANAGER, BudgieDesktopManager))
#define BUDGIE_IS_DESKTOP_MANAGER(o) (G_TYPE_CHECK_INSTANCE_TYPE((o), BUDGIE_TYPE_DESKTOP_MANAGER))
#define BUDGIE_DESKTOP_MANAGER_CLASS(o) (G_TYPE_CHECK_CLASS_CAST((o), BUDGIE_TYPE_DESKTOP_MANAGER, BudgieDesktopManagerClass))
#define BUDGIE_IS_DESKTOP_MANAGER_CLASS(o) (G_TYPE_CHECK_CLASS_TYPE((o), BUDGIE_TYPE_DESKTOP_MANAGER))
#define BUDGIE_DESKTOP_MANAGER_GET_CLASS(o)                                                                  \
        (G_TYPE_INSTANCE_GET_CLASS((o), BUDGIE_TYPE_DESKTOP_MANAGER, BudgieDesktopManagerClass))

GType budgie_desktop_manager_get_type(void);

/**
 * API Methods
 */

GList *budgie_desktop_manager_get_panels(BudgieDesktopManager *self);

guint budgie_desktop_manager_slots_available(BudgieDesktopManager *self);
guint budgie_desktop_manager_slots_used(BudgieDesktopManager *self);

void budgie_desktop_manager_set_placement(BudgieDesktopManager *self, const gchar *uuid, BudgiePanelPosition position);
void budgie_desktop_manager_set_transparency(BudgieDesktopManager *self, const gchar *uuid, BudgiePanelTransparency transparency);
void budgie_desktop_manager_set_size(BudgieDesktopManager *self, const gchar *uuid, gint new_size);

void budgie_desktop_manager_create_new_panel(BudgieDesktopManager *self);
void budgie_desktop_manager_delete_panel(BudgieDesktopManager *self, const gchar *uuid);

GList *budgie_desktop_manager_get_panel_plugins(BudgieDesktopManager *self);

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
