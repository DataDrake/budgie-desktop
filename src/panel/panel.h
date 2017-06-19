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

#pragma once

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _BudgiePanel BudgiePanel;
typedef struct _BudgiePanelClass BudgiePanelClass;

struct _BudgiePanelClass {
        GtkWindowClass parent_class;
};

/**
 * BudgiePanel is a GtkWindow based panel on screen, with it's own separate
 * state and applets. This is the main visible component on screen within the
 * Budgie Desktop.
 */
struct _BudgiePanel {
        GtkWindow parent;
};

#define BUDGIE_TYPE_PANEL budgie_panel_get_type()
#define BUDGIE_PANEL(o) (G_TYPE_CHECK_INSTANCE_CAST((o), BUDGIE_TYPE_PANEL, BudgiePanel))
#define BUDGIE_IS_PANEL(o) (G_TYPE_CHECK_INSTANCE_TYPE((o), BUDGIE_TYPE_PANEL))
#define BUDGIE_PANEL_CLASS(o) (G_TYPE_CHECK_CLASS_CAST((o), BUDGIE_TYPE_PANEL, BudgiePanelClass))
#define BUDGIE_IS_PANEL_CLASS(o) (G_TYPE_CHECK_CLASS_TYPE((o), BUDGIE_TYPE_PANEL))
#define BUDGIE_PANEL_GET_CLASS(o)                                                                  \
        (G_TYPE_INSTANCE_GET_CLASS((o), BUDGIE_TYPE_PANEL, BudgiePanelClass))

GType budgie_panel_get_type(void);

/**
 * Construct a new BudgiePanel
 */
GtkWidget *budgie_panel_new(void);

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
